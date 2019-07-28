#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Checks sets have been made to calculate structure functions
// Parameters:
//   None
// Outputs:
//   None
void RSoft::CheckSets()
{
  if(!setPos)
  {
    std::cout << "\nERROR: Must set positions using SetPos to calculate";
    std::cout << " structure functions.\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(!setBB)
  {
    std::cout << "\nERROR: Must set box boundaries using SetBB to";
    std::cout << " calculate structure functions.\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(!setBC)
  {
    std::cout << "\nERROR: Must set boundary conditions using SetBC to";
    std::cout << " calculate structure functions.\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(!setType && !checkSets)
  {
    std::cout << "WARNING: Types have not been set using SetType.";
    std::cout << " Assuming all particles are of type 1.\n";
    std::cout << std::flush;
  }
  if(!setType)
  {
    type.clear();
    for(int pp=0; pp<n_p; pp++)
    {
        type.push_back(1);
    }
  }
  
  // Marks program as having run
  checkSets = true; 

}
