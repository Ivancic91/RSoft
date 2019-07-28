#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <ctime>

// Gets softness
// Parameters:
//   radial_SF: 1D vector of softness values for each particle
// Outputs:
//   None
void RSoft::GetSoftness(std::vector<double>& soft)
{
  if(not openPlaneI)
  {
    std::cout << "ERROR: Must use OpenPlaneI before GetSoftness\n";
    std::exit(-1);
  }

  soft.clear();
  soft.resize(n_p);
  if(containsRadial)
  {
    if(not calculateRadialSFs)
    {
      CalculateRadialSFs();
    }
    for(int p=0; p<n_p; p++)
    {
      for(int SF=0; SF<n_SF_rad; SF++)
      {
        soft[p] += radial_plane[type[p]-1][SF]*SFs_radial[p][SF];
      }
    }
  }
  if(containsAngular)
  {
    if(not calculateAngularSFs)
    {
      CalculateAngularSFs();
    }
    for(int p=0; p<n_p; p++)
    {
      for(int SF=0; SF<n_SF_ang; SF++)
      {
        soft[p] += angular_plane[type[p]-1][SF]*SFs_angular[p][SF];
      }
    }
  }

  for(int p=0; p<n_p; p++)
  {
    soft[p] += intercept[type[p]-1];
  }

  getSoftness = true;

}
