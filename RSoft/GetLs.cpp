#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets Ls used to calculate structure functions
// Parameters:
//   Ls_: 1D vector to store L structure function parameters
// Outputs:
//   None
void RSoft::GetLs(std::vector<double>& Ls_)
{
  if(not openPlaneI and not openSFI)
  {
    std::cout << "ERROR: Must use OpenPlaneI or OpenSFI before GetLs\n";
    std::exit(-1);
  }

  Ls_ = Ls;

}
