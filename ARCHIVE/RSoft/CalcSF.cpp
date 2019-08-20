#include "RSoft/RSoft.hpp"
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>


/**********************************************************************
 * CalcSF
 *
 * This is a code that takes an AMBER format trajectory as well as an
 * RSoftSF file (which defines a set of structure functions) and 
 * outputs an RSoftSF file in which every structure function is 
 * evaluated, i.e. an RSoftSF file with particles. This file can be
 * used to train a softness hyperplane using RSoftPython tools. More
 * information can be found at: https://github.com/Ivancic91/RSoft.
 * 
 * @param[in] nc_read AMBER format trajectory name to input
 * @param[in] RSoftSF_read RSoftSF name of file to define RSoft 
 *       structure funcitons
 * @param[in] bc_x boundary condition in the x-direction, p = periodic,
 *       s = shrink wrapped, f = fixed.
 * @param[in] bc_y boundary condition in the y-direction
 * @param[in] bc_z boundary condition in the z-direction, if dataset
 *       is 2D please mark this n = none.
 * @param[in] RSoftSF_write RSoftSF name of file to define RSoft 
 *       structure funcitons
 *
 *********************************************************************/
int main(int argc, char* argv[])
{

  std::string str_read, str_RSoftSF_read, str_RSoftSF_write, str_bc;
  std::vector<std::string> bc;
  std::vector< std::vector<double> > pos_t, bb_t, SF_t;
  std::vector<int> type_t;
  int n_f;

  if(argc!=7)
  {   
    std::cout << "INPUT FORM: './CalcSF [nc_read] [RSoftSF_read] ";
    std::cout << "[bc_x] [bc_y] [bc_z] [RSoftSF_write]'\n";
    assert(argc==7);
  }   
  else
  {   
    str_read = argv[1];
    str_RSoftSF_read = argv[2];
    str_bc = argv[3];
    bc.push_back(str_bc);
    str_bc = argv[4];
    bc.push_back(str_bc);
    str_bc = argv[5];
    if(str_bc!="n")
    {   
      bc.push_back(str_bc);
    }   
    str_RSoftSF_write = argv[6];

  }  


  // Opens RSoft and DumpIO objects
  RSoft rs;
  rs.OpenSFO(str_RSoftSF_write);
  rs.OpenSFI(str_RSoftSF_read);
  NetCDFIO nc_read;
  nc_read.OpenI(str_read);
  n_f = nc_read.NumFrames();

  for(int f=0; f<n_f; f++)
  {
    // Prints current frame
    std::cout << "frame = " << f << "/" << n_f << "\n";
    std::cout << std::flush;

    // Gets positions and box boundaries
    nc_read.GetPos(f, pos_t);
    nc_read.GetBB(f, bb_t);

    // Sets positions, box boundaries, and boundary conditions
    rs.SetPos(pos_t);
    rs.SetBB(bb_t);
    rs.SetBC(bc);

    // Writes structure functions to output file
    rs.WriteSFs(f);
  }


  rs.CloseSFO();
  rs.CloseSFI();
}
