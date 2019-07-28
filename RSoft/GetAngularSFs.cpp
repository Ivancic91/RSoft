#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets angular structure functions that have been calculated
// Parameters:
//   angular_SF: 2D vector of vectors to store radial SF array in
// Outputs:
//   None
void RSoft::GetAngularSFs(std::vector< std::vector<double> >& SFs)
{
  if(not calculateAngularSFs)
  {
    CalculateAngularSFs();
  }
  SFs = SFs_angular;
  getAngularSFs = true;

}
