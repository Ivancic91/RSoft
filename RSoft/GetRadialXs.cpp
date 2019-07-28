#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets radial X structure function parameters
// Parameters:
//   type_Xs: 1D vector to store radial Xs of structure functions
// Outputs:
//   None
void RSoft::GetRadialXs(std::vector<int>& type_Xs)
{
  if(not openPlaneI and not openSFI)
  {
    std::cout << "ERROR: Must use OpenPlaneI or OpenSFI before";
    std::cout << " GetRadialXs\n";
    std::exit(-1);
  }

  type_Xs = radial_Xs;

}
