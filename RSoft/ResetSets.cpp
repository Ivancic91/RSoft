#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Resets sets after CalculateRadial and CalculateAngular have been
// run. This forces user to change particle positions and not
// stupidly calculate the same structure functions again.
// Parameters:
//   None
// Outputs:
//   None
void RSoft::ResetSets()
{
  if(calculateRadialSFs && calculateAngularSFs)
  {
    setPos = false;
    setType = false;
    checkNumParts = false;
  }
}
