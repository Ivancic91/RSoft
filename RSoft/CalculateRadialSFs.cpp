#include "RSoft.hpp"
#include "../MDTools/MDTools.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>

// Calculates the radial structure functions for all particles in 
// pos with box boundaries bb with boundary conditions bc and 
// types type.
// Parameters:
//   None
// Outputs:
//   None
void RSoft::CalculateRadialSFs()
{
  // Ensures Set functions properly used
  CheckSets();

  // Initializes number of neighbors variable
  int n_neigh;

  // Gets neighbor list, calculates Rc for the radial structure
  // functions, and initializes SFs_radial
  CalculateNListRList();
  SFs_radial.resize(n_p);
  for(int pp=0; pp<n_p; pp++)
  {
    SFs_radial[pp].resize(n_SF_rad);
    std::fill(SFs_radial[pp].begin(), SFs_radial[pp].end(), 0);
  }

  // For each particle, calculates structure functions from all
  // neighbors
  for(int pp=0; pp<n_p; pp++)
  {
    n_neigh = n_list_radial[pp].size();
    for(int nn=0; nn<n_neigh; nn++)
    {
      CalculateRadialSF_p_n(pp, nn);
    }
  }

  // resets set parameters and marks radial functions calculated
  ResetSets();
  calculateRadialSFs = true;
}
