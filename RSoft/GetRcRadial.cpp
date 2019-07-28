#include "RSoft.hpp"
#include  <math.h>
#include <iostream>
#include <cstdlib>

// Finds cutoff radius for neighbor list. If none was specified,
// chooses cutoff to ensure that all terms in sum are included if
// they are larger than 10^(-2).
// Parameters:
//   None
// Outputs:
//   Rc: double describing the cutoff radius for radial SFs for 
double RSoft::GetRcRadial()
{
  double Rc_max=0.0;
  double Rc_test;
  log_inv_etol_radial = log(1/etol_radial);

  for(int SF=0; SF<n_SF_rad; SF++)
  {
    Rc_test = mus[SF] + sqrt(log_inv_etol_radial)*Ls[SF];
    if(Rc_test > Rc_max)
    {
      Rc_max = Rc_test;
    }
  }

  return Rc_max;
}
