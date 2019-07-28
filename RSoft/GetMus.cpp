#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets mus used to calculate structure functions
// Parameters:
//   mus_: 1D vector of mus used for structure functions
// Outputs:
//   None
void RSoft::GetMus(std::vector<double>& mus_)
{
  if(not openPlaneI and not openSFI)
  {
    std::cout << "ERROR: Must use OpenPlaneI or OpenSFI before ";
    std::cout << "GetMus\n";
    std::exit(-1);
  }

  mus_ = mus;

}
