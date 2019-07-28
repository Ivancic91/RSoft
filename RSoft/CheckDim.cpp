#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Checks dimension d
// Parameters:
//   num_dims: int for number of dimensions
// Outputs:
//   None
void RSoft::CheckDim(int num_dims)
{

  if(checkDim && d!=num_dims)
  {
    std::cout << "\nERROR: Number of dimensions is not consistent";
    std::cout << " across arrays. Check pos_t, bb_t, and bc arrays.\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  else
  {
    d = num_dims;
  }

  checkDim = true;
}
