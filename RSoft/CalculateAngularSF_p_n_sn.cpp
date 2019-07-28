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
void RSoft::CalculateAngularSF_p_n_sn(
  int i,   // id of particle i
  int n_j, // index in neighbor list of i of particle j
  int n_k) // index in neighbor list of i of particle k
{

  // Declares variables
  MDTools tool;
  int j, k;                    // j, k ids
  int type_i, type_j, type_k;  // particle types
  int X, Y, Z;                 // SF types
  int zeta, lambda;
  double R_ij, R_ik, R_jk;     // distances between particles
  double cos_ijk, cos_jik;     // three body interactions
  double cos_kij;              // 
  double xi, exp_arg;          // xis and argument for exponential
  double ee;                   // SF term
  std::vector<double> r_ij, r_ik, r_jk;

  // Initializes particle j and k ids
  j = n_list_angular[i][n_j];
  k = n_list_angular[i][n_k];

  // Adds nothing if j <= i so that no double counting occurs
  if((k>j)&&(j>i))
  {
    // Initializes type and vector variables
    type_i = type[i];
    type_j = type[j];
    type_k = type[k];
    tool.DeltaR(pos[j], pos[i], bb, bc, r_ij);
    tool.DeltaR(pos[k], pos[i], bb, bc, r_ik);
    tool.DeltaR(pos[k], pos[j], bb, bc, r_jk);

    // Initializes distance variables
    R_ij = R_list_angular[i][n_j];
    R_ik = R_list_angular[i][n_k];
    R_jk = 0.0;
    for(int dd=0; dd<d; dd++)
    {
      R_jk += r_jk[dd]*r_jk[dd];
    }
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

    for(int SF=0; SF<n_SF_ang; SF++)
    {
      // Initializes structure function types
      X = angular_Xs[SF];
      Y = angular_Ys[SF];
      Z = angular_Zs[SF];
      xi = xis[SF];
      zeta = zetas[SF];
      lambda = lambdas[SF];

      // particle triple ijk
      if(type_i==X&&((type_j==Y&&type_k==Z)||(type_j==Z&&type_k==Y)))
      {
        exp_arg = (R_ij*R_ij+R_ik*R_ik+R_jk*R_jk)/(xi*xi);
        if(exp_arg<log_inv_etol_angular)
        {
          ee = exp(-exp_arg)*std::pow((1.0+lambda*cos_ijk)/2.0,zeta);
          ee = ee - etol_angular;
          if(type_j==Y&&type_k==Z&&ee>0)
          {
            SFs_angular[i][SF] += ee;
          }
          if(type_j==Z&&type_k==Y&&ee>0)
          {
            SFs_angular[i][SF] += ee;
          }
        }
      }
    
      // particle triple jik
      if(type_j==X&&((type_i==Y&&type_k==Z)||(type_i==Z&&type_k==Y)))
      {
        exp_arg = (R_ij*R_ij+R_ik*R_ik+R_jk*R_jk)/(xi*xi);
        if(exp_arg<log_inv_etol_angular)
        {
          ee = exp(-exp_arg)*std::pow((1.0+lambda*cos_jik)/2.0,zeta);
          ee = ee - etol_angular;
          if(type_i==Y&&type_k==Z&&ee>0)
          {
            SFs_angular[j][SF] += ee;
          }
          if(type_i==Z&&type_k==Y&&ee>0)
          {
            SFs_angular[j][SF] += ee;
          }
        }
      } 

      // particle triple kij
      if(type_k==X&&((type_i==Y&&type_j==Z)||(type_i==Z&&type_j==Y)))
      {
        exp_arg = (R_ij*R_ij+R_ik*R_ik+R_jk*R_jk)/(xi*xi);
        if(exp_arg<log_inv_etol_angular)
        {
          ee = exp(-exp_arg)*std::pow((1.0+lambda*cos_kij)/2.0,zeta);
          ee = ee - etol_angular;
          if(type_i==Y&&type_j==Z&&ee>0)
          {
            SFs_angular[k][SF] += ee;
          }
          if(type_i==Z&&type_j==Y&&ee>0)
          {
            SFs_angular[k][SF] += ee;
          }
        }
      }

    }
  }
}
