#include "RSoft.hpp"
#include  <math.h>
#include <iostream>

// Finds cutoff angular for neighbor list. If none was specified,
// chooses cutoff to ensure that all terms in sum are included if
// they are larger than 10^(-2).
// Parameters:
//   None
// Outputs:
//   Rc: double describing the cutoff radius for radial SFs for 
double RSoft::GetRcAngular()
{
  double Rc_max = 0.0;
  double Rc, xi, lambda;
  log_inv_etol_angular = log(1/etol_angular);

  // Finds angular structure function cutoff
  for(int SF=0; SF<n_SF_ang; SF++)
  {
    xi = xis[SF];
    lambda = lambdas[SF];
    if(lambda==1)
    {
      Rc = xi*sqrt(2.0*log_inv_etol_angular/3.0);
    }
    else
    {
      Rc = xi*sqrt(log_inv_etol_angular/2.0);
    }

    // Takes maximum cut-off of all structure functions as 
    // angular cutoff
    if(Rc > Rc_max)
    {
      Rc_max = Rc;
    }

  }
  return Rc_max;
}
