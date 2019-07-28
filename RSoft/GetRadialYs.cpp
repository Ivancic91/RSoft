#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets radial Ys 
// Parameters:
//   type_Ys: 1D vector to store radial structure function Y parameters
// Outputs:
//   None
void RSoft::GetRadialYs(std::vector<int>& type_Ys)
{
  if(not openPlaneI and not openSFI)
  {
    std::cout << "ERROR: Must use OpenPlaneI or OpenSFI before ";
    std::cout << "GetRadialYs\n";
    std::exit(-1);
  }

  type_Ys = radial_Ys;

}
