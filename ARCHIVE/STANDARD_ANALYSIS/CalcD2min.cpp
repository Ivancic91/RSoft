#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <stdlib.h>
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include "MDTools/MDTools.hpp"
#include "DynamicMeasures/DynamicMeasures.hpp"

/**********************************************************************
 * CalcD2min
 *
 * This is a code that takes every frame in an AMBER format trajectory
 * and outputs another AMBER format trajectory which contains the 
 * D^2_{min} of each particle as a data column. If a particle in the 
 * original neighbor list goes missing, i.e. its position is nan, the
 * D^2_{min} of the given particle will be nan. More information about
 * D^2_{min} is available at: Falk and Langer, Phy. Rev. E (1998). 
 *
 * @param[in] nc_read AMBER format trajectory name to input
 * @param[in] delta_frames number of frames in the lag time
 * @param[in] R_c cutoff radius of D^2_{min}
 * @param[in] bc_x boundary condition in the x-direction, p = periodic,
 *       s = shrink wrapped, f = fixed.
 * @param[in] bc_y boundary condition in the y-direction
 * @param[in] bc_z boundary condition in the z-direction, if dataset
 *       is 2D please mark this n = none.
 * @param[in] nc_write AMBER format trajectory name to output
 *
 *********************************************************************/
int main(int argc, char* argv[])
{

  // Declares variables
  std::string str_read, str_write, str_bc;
  int n_f, df, t;
  double R_c;
  std::vector< std::vector<double> > pos_t, pos_dt, bb_t, bb_dt;
  std::vector<double> d2min_t, radius_t;
  std::vector<int> type_t;
  std::vector< std::vector<int> > n_list_t;
  std::vector<std::string> bc; 

  // Catches errors in the input form
  if(argc!=8)
  {
    std::cout << "INPUT FORM: './CalcD2min [nc_read] [delta_frames]";
    std::cout << " [R_c] [bc_x] [bc_y] [bc_z] [nc_write]'\n";
    assert(argc==8);
  }
  else
  {
    str_read = argv[1];
    df = atoi(argv[2]);
    R_c = atof(argv[3]);
    str_bc = argv[4];
    bc.push_back(str_bc);
    str_bc = argv[5];
    bc.push_back(str_bc);
    str_bc = argv[6];
    if(str_bc!="n")
    {
      bc.push_back(str_bc);
    }
    str_write = argv[7];
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

    // Reads timestep, box boundaries, positons, and types at frame f
    // Reads box boundaries and positions at frame f+df
    nc_file_read.Gett(f, t);
    nc_file_read.GetBB(f, bb_t);
    nc_file_read.GetPos(f, pos_t);
    nc_file_read.GetDataCol(f, "type", type_t);
    nc_file_read.GetBB(f+df, bb_dt);
    nc_file_read.GetPos(f+df, pos_dt);
    // nc_file_read.GetDataCol(f, "Radius", radius_t);
    // ^ The above line may be uncommented and modified if there is 
    //       another data column from the original file one wishes to
    //       include in the D^2_{min} file.

    // Calculates d2min for all particles
    tool.PostProcess(pos_t,bb_t,bc);
    tool.PostProcess(pos_dt,bb_dt,bc);
    tool.GetNList(pos_t, bb_t, bc, R_c, n_list_t);
    dm.D2minAllParticles(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, d2min_t);

    // Writes positions, boundaries, time, and j2 for time t
    nc_file_write.Sett(f, t);
    nc_file_write.SetBB(f, bb_t);
    nc_file_write.SetPos(f, pos_t);
    nc_file_write.SetDataCol(f, "type", type_t);
    nc_file_write.SetDataCol(f, "d2min", d2min_t);
    // nc_file_write.SetDataCol(f,"Radius", radius_t);
    // ^ The above line may be uncommented and modified if there is 
    //       another data column from the original file one wishes to
    //       include in the D^2_{min} file.
  }

  nc_file_read.CloseI();
  nc_file_write.CloseO();

  std::cout << "\n\n DONE \n\n";

  return 0;

}
