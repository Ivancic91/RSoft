#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Checks number of particles n_p
// Parameters:
//   num_parts: int for number of particles
// Outputs:
//   None
void RSoft::CheckNumParts(int num_parts)
{

  if(checkNumParts && n_p!=num_parts)
  {
    std::cout << "ERROR: Number of particles is not consistent";
    std::cout << " across arrays. Check pos_t and type_t arrays.\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  else
  {
    n_p = num_parts;
  }

  checkNumParts = true;
}
