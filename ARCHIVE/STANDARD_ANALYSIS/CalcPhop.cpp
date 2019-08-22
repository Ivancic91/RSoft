#include <fstream>
#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <math.h>
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include "MDTools/MDTools.hpp"
#include "DynamicMeasures/DynamicMeasures.hpp"
#define _USE_MATH_DEFINES


/**********************************************************************
 * CalcPhop
 * 
 * This is a code that takes every frame in an AMBER format trajectory
 * and outputs another AMBER format trajectory which contains the 
 * p_{hop} of each particle as a data column. If a particle's positions
 * are nan at any point in t_R, then gives a p_{hop} of nan. More 
 * information about p_{hop} is available: Smessaert and Rottler, Phys.
 * Rev. E (2013).
 *
 * @param[in] nc_read AMBER format trajectory name to input
 * @param[in] tR number of frames commenserate with a rearrangement
 * @param[in] bc_x boundary condition in the x-direction, p = periodic,
 *       s = shrink wrapped, f = fixed.
 * @param[in] bc_y boundary condition in the y-direction
 * @param[in] bc_z boundary condition in the z-direction, if dataset
 *       is 2D please mark this n = none.
 * @param[in] nc_write AMBER format trajectory name to output
 *
 **********************************************************************/
int main(int argc, char* argv[])
{

  // Declares all variables
  std::string str_read, str_write, str_bc;
  int n_f, n_p, t, tR, tR_frame;
  std::vector< std::vector<double> > bb_t;
  std::vector< std::vector<double> > pos_t;
  std::vector< std::vector< std::vector<double> > > pos;
  std::vector<double> type;
  std::vector<double> phop_t;
  std::vector<std::string> bc;
  MDTools tool;
  DynamicMeasures dm;

  if (argc != 7)
  {
    std::cout << "ERROR: Must have input: \n\
      \'./Phop [nc_read] [tR] [bc_x] [bc_y] [bc_z] [nc_write]\'\n"
      << std::flush;
      assert(argc == 7);
  }
  else
  {

    str_read = argv[1];
    tR = atoi(argv[2]);
    str_bc = argv[3];
    bc.push_back(str_bc);
    str_bc = argv[4];
    bc.push_back(str_bc);
    str_bc = argv[5];
    if(str_bc!="n")
    {   
      bc.push_back(str_bc);
    }   
    str_write = argv[6];
  }

  // Gets number of frames and particles
  NetCDFIO nc_read;
  nc_read.OpenI(str_read);
  n_f = nc_read.NumFrames();
  n_p = nc_read.NumParts();
  
  // Gets number of frames and particles
  NetCDFIO nc_write;
  nc_write.OpenO(str_write);

  // Adds first positions to pos
  for(int f=0; f<tR+1; f++)
  {
    nc_read.GetPos(f, pos_t);
    nc_read.GetBB(f, bb_t);
    tool.PostProcess(pos_t, bb_t, bc);
    pos.push_back(pos_t);
  }

  // Calculates and saves phop for every frame
  tR_frame = tR/2;
  for(int f=tR/2; f<n_f-tR/2; f++)
  {

    // Outputs which frame we are working on
    std::cout << "Frame = " << f << "\n";

    // Gets all data from frame
    nc_read.Gett(f, t);
    nc_read.GetPos(f, pos_t);
    nc_read.GetBB(f, bb_t);
    nc_read.GetDataCol(f, "type", type);
    // nc_file_read.GetDataCol(f, "Radius", radius_t);
    //   ^ The above line may be uncommented and modified if there is 
    //       another data column from the original file one wishes to
    //       include in the p_{hop} file.

    // Calculates p_{hop} for the current frame
    tool.PostProcess(pos_t, bb_t, bc);
    dm.PhopAllParticles(pos, bb_t, bc, tR_frame, tR, phop_t);

    // Writes box boundaries and positions
    nc_write.Sett(f-tR/2, t);
    nc_write.SetBB(f-tR/2, bb_t);
    nc_write.SetPos(f-tR/2, pos_t);
    nc_write.SetDataCol(f-tR/2, "type", type);
    nc_write.SetDataCol(f-tR/2, "phop", phop_t);
    // nc_file_write.SetDataCol(f,"Radius", radius_t);
    //   ^ The above line may be uncommented and modified if there is 
    //     another data column from the original file one wishes to
    //     include in the p_{hop} file.

    // Updates pos for new positions
    // except for last frame
    if(f<n_f-tR/2-1)
    {
      nc_read.GetPos(f+tR/2+1, pos_t);
      tool.PostProcess(pos_t, bb_t, bc);
      pos.push_back(pos_t);
      pos.erase(pos.begin());
    }
  }


  nc_read.CloseI();
  nc_write.CloseO();
  std::cout << "****Success!! :)\n";
  return 0;
  
}
