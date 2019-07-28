#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <cmath>

// Calculates the angular structure functions for all particles in 
// pos with box boundaries bb with boundary conditions bc and 
// types type.
// Parameters:
//   None
// Outputs:
//   None
void RSoft::CalculateAngularSFs()
{

  std::vector<int> SF_idx_arr;

  // Checks all positions, boundaries, boundary conditions, and types
  // are set
  CheckSets();

  // Initializes several variables
  bool XXeqYY, XXeqZZ, YYeqZZ;
  int n_neigh, tt, type_XX, type_YY, type_ZZ;
  std::vector<int> n_list_Y, n_list_Z;

  // Gets neighbor list, r list, and initializes angular SF array.
  CalculateNListRList();
  SFs_angular.resize(n_p);
  for(int pp=0; pp<n_p; pp++)
  {
    SFs_angular[pp].resize(n_SF_ang);
    std::fill(SFs_angular[pp].begin(), SFs_angular[pp].end(), 0);
  }

  for(unsigned int XX=0; XX<unique_angular_Xs.size(); XX++)
  {
    type_XX = unique_angular_Xs[XX];
    for(unsigned int YY=0; YY<unique_angular_Ys.size(); YY++)
    {
      type_YY = unique_angular_Ys[YY];
      for(unsigned int ZZ=0; ZZ<unique_angular_Zs.size(); ZZ++)
      {
        type_ZZ = unique_angular_Zs[ZZ];

        // Creates a list of structure functions to evaluate
        SF_idx_arr.clear();
        for(int SF=0; SF<n_SF_ang; SF++)
        {
          if(angular_Xs[SF]==type_XX and angular_Ys[SF]==type_YY
                and angular_Zs[SF]==type_ZZ)
          {
            SF_idx_arr.push_back(SF);
          }
        }

        // Finds which types are the same
        XXeqYY = (type_XX==type_YY);
        XXeqZZ = (type_XX==type_ZZ);
        YYeqZZ = (type_YY==type_ZZ);

        for(int pp=0; pp<n_p; pp++)
        {
          tt = type[pp];
          if(type_XX == tt)
          {
            // Creates neighbor lists of type Y and Z particles
            n_list_Y.clear();
            n_list_Z.clear();
            n_neigh = n_list_angular[pp].size();
            for(int neigh=0; neigh<n_neigh; neigh++)
            {
              tt = type[n_list_angular[pp][neigh]];
              if(type_YY==tt)
                n_list_Y.push_back(n_list_angular[pp][neigh]);
              if(type_ZZ==tt)
                n_list_Z.push_back(n_list_angular[pp][neigh]);
            }
            CalculateAngularSFs_p(pp, SF_idx_arr, n_list_Y, n_list_Z, 
                   XXeqYY, XXeqZZ, YYeqZZ);
          } 
        }
      }
    }
  }

  // resets set parameters and marks radial functions calculated
  ResetSets();
  calculateAngularSFs = true;
}
