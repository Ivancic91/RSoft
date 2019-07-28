/* Calculates J2 of every frame */
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdlib.h>
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include "MDTools/MDTools.hpp"
#include "DynamicMeasures/DynamicMeasures.hpp"

int main(int argc, char* argv[])
{

  // Declares variables
  std::string str_read, str_write;
  int n_f, df, t;
  std::vector< std::vector<double> > pos_t, pos_dt, bb_t, bb_dt;
  std::vector<double> d2min_t, radius_t;
  std::vector< std::vector<int> > n_list_t;

  // Declares and initializes bc and R_c
  double R_c = 2.5;
  std::vector<std::string> bc;
  bc.push_back("s");
  bc.push_back("s");
  bc.push_back("s");

  if(argc!=4)
  {
    std::cout << "INPUT FORM: './CalcD2min [nc_read] [nc_write] [delta_frames]'\n";
    assert(argc==4);
  }
  else
  {
    str_read = argv[1];
    str_write = argv[2];
    df = atoi(argv[3]);
  }

  // Creates NetCDFIO objects for reading and writing
  NetCDFIO nc_file_read;
  nc_file_read.OpenI(str_read);
  NetCDFIO nc_file_write;
  nc_file_write.OpenO(str_write);

  // Creates tool from MDTool
  MDTools tool;
  DynamicMeasures dm;


  n_f = nc_file_read.NumFrames();
  for(int f=0; f<n_f-df; f++)
  {
    std::cout << "f = " << f << " / " << n_f-df << "\n" << std::flush;

    // Reads posiitons and boundaries at time t
    n_f = nc_file_read.NumFrames();
    nc_file_read.Gett(f, t);
    nc_file_read.GetBB(f, bb_t);
    nc_file_read.GetPos(f, pos_t);
    nc_file_read.GetBB(f+df, bb_dt);
    nc_file_read.GetPos(f+df, pos_dt);
    nc_file_read.GetDataCol(f, "Radius", radius_t);

    // Calculates d2min for all particles
    tool.PostProcess(pos_t,bb_t,bc);
    tool.PostProcess(pos_dt,bb_dt,bc);
    tool.GetNList(pos_t, bb_t, bc, R_c, n_list_t);
    dm.D2minAllParticles(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, d2min_t);

    // Writes positions, boundaries, time, and j2 for time t
    nc_file_write.Sett(f, t);
    nc_file_write.SetBB(f, bb_t);
    nc_file_write.SetPos(f, pos_t);
    nc_file_write.SetDataCol(f, "d2min", d2min_t);
    nc_file_write.SetDataCol(f,"Radius", radius_t);
  }

  nc_file_read.CloseI();
  nc_file_write.CloseO();

  std::cout << "\n\n DONE \n\n";

  return 0;

}
