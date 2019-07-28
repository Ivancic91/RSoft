/* Finds g_{A,B}(r) for a simulation from f_start to f_end.
 * Assumes number of particles and particle types are unchanged
 * between f_start and f_end.
 */
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdlib.h>
#include "LammpsIO/DumpIO/DumpIO.hpp"
#include "RSoft/RSoft.hpp"
#include "MDTools/MDTools.hpp"

int main(int argc, char* argv[])
{

    // Declares variables
    char i_char[10], j_char[10];
    std::string i_str, j_str, tmp;
    std::string str_dump_read, str_RSoft_I, str_out;
    int f_start, f_end, n_p, n_SF, type_i, type_j, n_type_i, n_type_j;
    double etol, sqrt_log_inv, rho_j;
    double pi = 3.14159265, C, vol_tmp, vol=0;
    std::vector<int> type_t, type_is, type_js;
    std::vector<int> unique_is, unique_js;
    std::vector<double> mus, Ls, gr_arr;
    std::vector< std::vector<double> > Gr, Gr_sum;
    std::vector< std::vector<double> > pos_t, bb_t;
    std::vector<std::string> bc; 

    if(argc!=8)
    {
      std::cout << "INPUT FORM: './gr [dump_read] [RSoftSF] [f_start] ";
      std::cout << "[f_end] [bc_x] [bc_y] [bc_z]'\n";
      assert(argc==8);
    }
    else
    {
      str_dump_read = argv[1];
      str_RSoft_I = argv[2];
      f_start = atoi(argv[3]);
      f_end = atoi(argv[4]);
      tmp = argv[5];
      bc.push_back(tmp);
      tmp = argv[6];
      bc.push_back(tmp);
      tmp = argv[7];
      bc.push_back(tmp);
    }

    // Creates NetCDFIO objects for reading and writing
    DumpIO dump;
    std::ifstream read_stream(str_dump_read.c_str());
    dump.OpenI(read_stream);
    n_p = dump.NumPartsCurrentf(read_stream);

    // Creates tool from MDTool
    MDTools tool;
    RSoft rs;
    rs.OpenSFI(str_RSoft_I);
    rs.GetMus(mus);
    rs.GetLs(Ls);
    rs.GetRadialXs(type_is);
    rs.GetRadialYs(type_js);
    rs.GetRadialEtol(etol);
    n_SF = mus.size();

    // Calculates constant C for SF normalization for g(r)
    sqrt_log_inv = sqrt(log(1.0/etol));
    C = 4.0*pi*(sqrt(pi)*erf(sqrt_log_inv)-2.0*etol*sqrt_log_inv);
    std::cout << C << "\n\n";

    // Initializes Gr_sum and unique_is/js
    Gr_sum.resize(n_p, std::vector<double>(n_SF));
    unique_is = type_is;
    std::sort(unique_is.begin(), unique_is.end());
    unique_is.erase(std::unique(unique_is.begin(), unique_is.end()),
          unique_is.end());
    unique_js = type_js;
    std::sort(unique_js.begin(), unique_js.end());
    unique_js.erase(std::unique(unique_js.begin(), unique_js.end()),
          unique_js.end());

    // Skips frames until the first one
    for(int f=0; f<f_start; f++)
    {
      dump.LoadNextFrame(read_stream);
    }

    for(int f=f_start; f<f_end; f++)
    {
      // Outputs frame
      std::cout << "frame = " << f << "\n";
      std::cout << std::flush;

      // Loads next frame
      dump.LoadNextFrame(read_stream);
      dump.SortByID();

      // Reads posiitons and boundaries at time t
      dump.GetBB(bb_t);
      dump.GetPos(pos_t);
      dump.GetDataCol("type",type_t);

      // Calculates radial SFs for particles
      tool.PostProcess(pos_t,bb_t,bc);
      rs.SetBB(bb_t);
      rs.SetPos(pos_t);
      rs.SetBC(bc);
      rs.SetType(type_t);
      rs.GetRadialSFs(Gr);

      // Sums Gr for all particles
      for(int pp=0; pp<n_p; pp++)
      {
        for(int SF=0; SF<n_SF; SF++)
        {
          Gr_sum[pp][SF] += Gr[pp][SF];
        }
      }

      vol_tmp = 1.0;
      for(int dd=0; dd<bb_t.size(); dd++)
      {      
        vol_tmp = vol_tmp * (bb_t[dd][1]-bb_t[dd][0]);
      }
      vol += vol_tmp;
    }

    // Finds g(r) for each set of SF parameters
    vol = vol / (f_end-f_start);
    std::cout << "v = " << vol << "\n";
    for(int SF=0; SF<n_SF; SF++)
    {
      n_type_i = 0;
      n_type_j = 0;
      gr_arr.push_back(0.0);
      for(int pp=0; pp<n_p; pp++)
      {
        gr_arr[SF] += Gr_sum[pp][SF];
        if(type_is[SF] == type_t[pp])
        {
          n_type_i += 1;
        }
        if(type_js[SF] == type_t[pp])
        {   
          n_type_j += 1;
        }  
      }
      rho_j = n_type_j / vol;
      gr_arr[SF] = gr_arr[SF] / (n_type_i*(f_end-f_start));
      gr_arr[SF] = gr_arr[SF] / rho_j;
      gr_arr[SF] = gr_arr[SF] / (C*mus[SF]*mus[SF]*Ls[SF]);
    }

    for(int ii = 0; ii < unique_is.size(); ii++)
    {
      type_i = unique_is[ii];
      for(int jj = 0; jj < unique_js.size(); jj++)
      {
        type_j = unique_js[jj];
        std::sprintf(i_char, "%d", type_i);
        i_str = i_char;
        std::sprintf(j_char, "%d", type_j);
        j_str = j_char;
        str_out = "gr_" + i_str + "_";
        str_out = str_out + j_str + ".dat";
        std::ofstream write_stream(str_out.c_str());
        for(int SF=0; SF<n_SF; SF++)
        {
          if(type_i==type_is[SF] and type_j==type_js[SF])
          {
            write_stream << mus[SF] << " " << gr_arr[SF] << "\n";
          }
        }
        write_stream.close();
      }
    }

    // Closes input file
    read_stream.close();

    return 0;

}
