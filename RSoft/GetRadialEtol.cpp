#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets radial error tolerance
// Parameters:
//   etol_rad: double to hold radial error tolerance
// Outputs:
//   None
void RSoft::GetRadialEtol(double& etol_rad)
{
  if(not openPlaneI and not openSFI)
  {
    std::cout << "ERROR: Must use OpenPlaneI or OpenSFI before ";
    std::cout << "GetRadialEtol\n";
    std::exit(-1);
  }

  etol_rad = etol_radial;

}
