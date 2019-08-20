#include "RSoft/RSoft.hpp"
#include "LammpsIO/DumpIO/DumpIO.hpp"
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>

/**********************************************************************
 * CalcSoft
 *
 * This is a code that takes an AMBER format trajectory as well as an
 * RSoftPlane file (which defines a set of structure functions as well
 * as a corresponding hyperplane) and 
 * outputs an RSoftSF file in which every structure function is 
 * evaluated, i.e. an RSoftSF file with particles. This file can be
 * used to train a softness hyperplane using RSoftPython tools. More
 * information can be found at: https://github.com/Ivancic91/RSoft.
 * 
 * @param[in] nc_read AMBER format trajectory name to input
 * @param[in] RSoftPlane RSoftPlane name of file to define RSoft 
 *       hyperplane
 * @param[in] bc_x boundary condition in the x-direction, p = periodic,
 *       s = shrink wrapped, f = fixed.
 * @param[in] bc_y boundary condition in the y-direction
 * @param[in] bc_z boundary condition in the z-direction, if dataset
 *       is 2D please mark this n = none.
 * @param[in] nc_write RSoftSF AMBER format trajectory name to input
 *
 **********************************************************************/
int main(int argc, char* argv[])
{

  std::string str_read, str_RSoftPlane, str_write, str_bc;
  std::vector<std::string> bc;
  std::vector< std::vector<double> > pos_t, bb_t;
  std::vector<int> type_t;
  std::vector<double> s_t;
  int n_f, t;

  if(argc!=7)
  {   
    std::cout << "INPUT FORM: './CalcSoft [nc_read] [RSoftPlane] ";
    std::cout << "[bc_x] [bc_y] [bc_z] [nc_write]'\n";
    assert(argc==7);
  }   
  else
  {   
    str_read = argv[1];
    str_RSoftPlane = argv[2];
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

  // Opens RSoft and DumpIO objects
  RSoft rs;
  rs.OpenPlaneI(str_RSoftPlane);
  NetCDFIO nc_read, nc_write;
  nc_read.OpenI(str_read);
  nc_write.OpenO(str_write);
  n_f = nc_read.NumFrames();

  for(int f=0; f<n_f; f++)
  {
    // Outputs current frame
    std::cout << "frame = " << f << "/" << n_f << "\n";
    std::cout << std::flush;

    // Inputs timestep, positions and box bounds from frame
    nc_read.Gett(f,t);
    nc_read.GetPos(f, pos_t);
    nc_read.GetBB(f, bb_t);
    // nc_file_read.GetDataCol(f, "Radius", radius_t);
    //   ^ The above line may be uncommented and modified if there is 
    //       another data column from the original file one wishes to
    //       include in the softness file.

    // Sets positions, box boundaries and boundary conditions of frame
    rs.SetPos(pos_t);
    rs.SetBB(bb_t);
    rs.SetBC(bc);

    // Calculates softness for each particle and stores as vector
    rs.GetSoftness(s_t);

    // Outputs time, position, box boundary and softness
    nc_write.Sett(f, t);
    nc_write.SetPos(f, pos_t);
    nc_write.SetBB(f, bb_t);
    nc_write.SetDataCol(f, "S", s_t);
    // nc_file_read.GetDataCol(f, "Radius", radius_t);
    //   ^ The above line may be uncommented and modified if there is 
    //       another data column from the original file one wishes to
    //       include in the softness file.
  }


  rs.ClosePlaneI();
  nc_read.CloseI();
  nc_write.CloseO();
}
