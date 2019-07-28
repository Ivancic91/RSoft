#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Gets radial structure functions that have been calculated
// Parameters:
//   radial_SF: 2D vector of vectors to store radial SF array in
// Outputs:
//   None
void RSoft::GetRadialSFs(std::vector< std::vector<double> >& SFs)
{

  if(not calculateRadialSFs)
  {
    CalculateRadialSFs();
  }
  SFs = SFs_radial;
  getRadialSFs = true;
}
