#include "RSoft.hpp"
#include "../MDTools/MDTools.hpp"
#include <cstdlib>
#include <math.h>
#include <cmath>
#include <iostream>

// Calculates angular structure function terms between particles i, j
// and k which are the n_jth and n_kth neighbors of particle i. NOTE:
//this function should only be used if softness for all particles is 
// being calculated as it adds all permutations of ijk terms to the 
// sum iff i<j<k
void RSoft::CalculateAngularSFs_p(
      int pp_i, 
      std::vector<int>& SF_idx_arr,
      std::vector<int>& n_list_j,
      std::vector<int>& n_list_k,
      bool IIeqJJ,
      bool IIeqKK,
      bool JJeqKK)
{

  // Declares variables
  MDTools tool;
  int pp_j, pp_k;
  int zeta, lambda, SF;
  double R_ij, R_ik, R_jk;      // distances between particles
  double cos_ijk, cos_jik;      // three body interactions
  double cos_kij;               // 
  double xi, exp_arg, exp_term; // xis and argument for exponential
  double ee;                    // SF term
  std::vector<double> pos_i, pos_j;
  std::vector<double> r_ij, r_ik, r_jk;

  // Loops through all j neighbors
  pos_i = pos[pp_i];
  for(unsigned int jj=0; jj<n_list_j.size(); jj++)
  {
    pp_j = n_list_j[jj];

    // Ensures no double counting if type_ii == type_jj
    if(pp_j > pp_i or not IIeqJJ)
    {

      pos_j = pos[pp_j];
      for(unsigned int kk=0; kk<n_list_k.size(); kk++)
      {
        pp_k = n_list_k[kk];

        // Ensures no double counting if type_ii == type_kk or
        // type_jj == type_kk
        if((pp_k > pp_i or not IIeqKK) and (pp_k > pp_j or not JJeqKK))
        {
          // Finds difference vectors between positions
          tool.DeltaR(pos_j, pos_i, bb, bc, r_ij);
          tool.DeltaR(pos[pp_k], pos_i, bb, bc, r_ik);
          tool.DeltaR(pos[pp_k], pos_j, bb, bc, r_jk);

          // Initializes distance variables
          R_ij = 0.0;
          R_ik = 0.0;
          R_jk = 0.0;
          for(int dd=0; dd<d; dd++)
          {
            R_ij += r_ij[dd]*r_ij[dd];
            R_ik += r_ik[dd]*r_ik[dd];
            R_jk += r_jk[dd]*r_jk[dd];
          }
          R_ij = sqrt(R_ij);
          R_ik = sqrt(R_ik);
          R_jk = sqrt(R_jk);

          // Initializes angular variables
          cos_ijk = 0.0;
          cos_jik = 0.0;
          cos_kij = 0.0;
          for(int dd=0; dd<d; dd++)
          {
            cos_ijk += (r_ij[dd]/R_ij)*(r_ik[dd]/R_ik);
            cos_jik += (-r_ij[dd]/R_ij)*(r_jk[dd]/R_jk);
            cos_kij += (-r_ik[dd]/R_ik)*(-r_jk[dd]/R_jk);
          }

          for(unsigned int idx=0; idx<SF_idx_arr.size(); idx++)
          {
            // Initializes structure function types
            SF = SF_idx_arr[idx];
            xi = xis[SF];
            zeta = zetas[SF];
            lambda = lambdas[SF];

            exp_arg = (R_ij*R_ij+R_ik*R_ik+R_jk*R_jk)/(xi*xi);
            if(exp_arg<log_inv_etol_angular)
            {

              // particle triple ijk
              exp_term = exp(-exp_arg);
              ee = exp_term*std::pow((1.0+lambda*cos_ijk)/2.0,zeta);
              ee = ee - etol_angular;
              if(ee > 0)
              {
                if(JJeqKK) // double counts if type_j==type_k
                  ee = 2.0*ee;
                SFs_angular[pp_i][SF] += ee;
              }

              // particle triple jik (if type_i == type_j)
              if(IIeqJJ)
              {
                ee = exp_term*std::pow((1.0+lambda*cos_jik)/2.0,zeta);
                ee = ee - etol_angular;
                if(ee > 0)
                {
                  if(IIeqKK) // double counts if type_i==type_k
                    ee = 2.0*ee;
                  SFs_angular[pp_j][SF] += ee;  
                }
              }

              // particle triple kij (if type_i == type_k)
              if(IIeqKK)
              {
                ee = exp_term*std::pow((1.0+lambda*cos_kij)/2.0,zeta);
                ee = ee - etol_angular;
                if(ee > 0)
                {
                  if(IIeqJJ) // double counts if type_i==type_j
                    ee = 2.0*ee;
                  SFs_angular[pp_k][SF] += ee; 
                }
              }
            }
          }
        }
      } 
    }
  }
}
