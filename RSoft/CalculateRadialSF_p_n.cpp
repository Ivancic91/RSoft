#include "RSoft.hpp"
#include "../MDTools/MDTools.hpp"
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <iostream>

// Calculates radial structure function terms between particles i and
// j which is the n_jth neighbor of particle i. NOTE this function 
// should only be used if softness for all particles is being
// calculated as it adds both ij and ji terms to the sum iff i<j
// Parameters:
//   None
// Outputs:
//   None
void RSoft::CalculateRadialSF_p_n(
  int i,   // id of particle i
  int n_j) // index in neighbor list of particle j
{

  // Declares variables
  int j, type_i, type_j; // j id and particle types
  int X, Y;              // SF types
  double R_ij, delta, L; 
  double exp_arg;
  double ee;             // SF term
  std::vector<double> r_ij;
  MDTools tool;

  // Initializes particle j id
  j = n_list_radial[i][n_j];
  //std::cout << i << "," << j << "," << type[i] << "," << type[j] << "\n";

  // Adds nothing if j <= i so that no double counting occurs
  if(j > i)
  {
    // Initializes type and distance variables
    type_i = type[i];
    type_j = type[j];
    tool.DeltaR(pos[j], pos[i], bb, bc, r_ij);
    R_ij = 0;
    for(int dd=0; dd<d; dd++)
    {   
      R_ij += r_ij[dd]*r_ij[dd];
    }   
    R_ij = sqrt(R_ij);

    for(int SF=0; SF<n_SF_rad; SF++)
    {
      // Initializes structure function types
      X = radial_Xs[SF];
      Y = radial_Ys[SF];

      // Checks if types match
      if((type_i==X&&type_j==Y)||(type_i==Y&&type_j==X))
      {
        // Initializes difference and L doubles
        delta = fabs(R_ij-mus[SF]);
        L = Ls[SF];
     
        // Checks if these particles are within range of SF
        exp_arg = (delta/L)*(delta/L);
        if(exp_arg < log_inv_etol_radial)
        {
          // Calculates exponent and subtracts etol_radial to 
          // ensure continuity.
          ee = exp(-exp_arg)-etol_radial;

          // Adds term to correct bins for i and j 
          if(type_i==X&&type_j==Y)
          {
            SFs_radial[i][SF] += ee;
          }
          if(type_i==Y&&type_j==X)
          {
            SFs_radial[j][SF] += ee;
          }
        }
      }
    }
  }
}
