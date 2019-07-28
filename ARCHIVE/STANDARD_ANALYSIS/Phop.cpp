/* Created to calculate Phop */
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

int main(int argc, char* argv[])
{

  // Declares all variables
  std::string nc_file_read, nc_file_write;
  int n_f, n_p, t, tR, tR_frame;
  std::string tR_str, col_str;
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
      \'./Phop [nc read] [nc write] [tR] [bc_x] [bc_y] [bc_z]\'\n"
      << std::flush;
      assert(argc == 7);
  }
  else
  {
    nc_file_read = argv[1];
    nc_file_write = argv[2];
    tR_str = argv[3];
    bc.push_back(argv[4]);
    bc.push_back(argv[5]);
    bc.push_back(argv[6]);

    tR = atoi(tR_str.c_str());
  }

  // Gets number of frames and particles
  NetCDFIO nc_read;
  nc_read.OpenI(nc_file_read);
  n_f = nc_read.NumFrames();
  n_p = nc_read.NumParts();

  // Gets number of frames and particles
  NetCDFIO nc_write;
  nc_write.OpenO(nc_file_write);

  col_str = "phop";

  // Adds first positions to pos
  for(int f=0; f<tR+1; f++)
  {
    nc_read.GetPos(f, pos_t);
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
    dm.PhopAllParticles(pos, bb_t, bc, tR_frame, tR, phop_t);

    // Post-Processts data at time t
    tool.PostProcess(pos_t, bb_t, bc);

    // Writes box boundaries and positions
    nc_write.Sett(f-tR/2, t);
    nc_write.SetBB(f-tR/2, bb_t);
    nc_write.SetPos(f-tR/2, pos_t);
    nc_write.SetDataCol(f-tR/2, "type", type);
    nc_write.SetDataCol(f-tR/2, "phop", phop_t);

    // Updates pos for new positions
    // except for last frame
    if(f<n_f-tR/2-1)
    {
      nc_read.GetPos(f+tR/2+1, pos_t);
      pos.push_back(pos_t);
      pos.erase(pos.begin());
    }
  }


  nc_read.CloseI();
  nc_write.CloseO();
  std::cout << "****Success!! :)\n";
  return 0;

}
