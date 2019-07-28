// This is an unfinished project!
#include "DynamicMeasures.hpp"
#include "../MDTools/MDTools.hpp"
#include "../Eigen/Dense"
#include <iostream>


void DynamicMeasures::LocalPlane(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector<double>& field_t,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  int m,
  std::vector<double>& plane_norm,
  double& intercept)
{

  // Declares variables
  int n_p, d, n_neigh, neigh;
  std::vector<double> temp_vec, R_m_t, R_neigh_t, dR_t_vec;
  typedef Eigen::Matrix<double, -1, -1> Mat;
  typedef Eigen::Matrix<double, -1, -1> Vec;
  MDTools tool;

  // Initializes variables
  n_p = pos_t.size();
  d = pos_t[0].size();

  n_neigh = n_list_t[m].size();
  //R_m_t = pos_t[m];
  Mat A(d+1,d+1), cov(d,d);
  Vec 
  A.setZero();
  cov.setZero();

  // Finds DR_t_DR_t and DR_dt_DR_t matrices
  for(int n=0; n<n_neigh; n++)
  {

    // Calculates delta R vectors at time t and t + dt
    neigh = n_list_t[m][n];
    R_neigh_t = pos_t[neigh];
    tool.DeltaR(R_neigh_t, R_m_t, bb_t, bc, dR_t_vec);

    // Initializes Eigen vectors to do LA computations
    Eigen::Map<Vec> dR_t(dR_t_vec.data(), d, 1);
    Eigen::Map<Vec> dR_dt(dR_dt_vec.data(), d, 1);

    // Outer product X and Y
    DR_t_DR_t = DR_t_DR_t + dR_t*(dR_t.transpose());
    DR_dt_DR_t = DR_dt_DR_t + dR_dt*(dR_t.transpose());

  }

  lambda_min_t = DR_dt_DR_t*(DR_t_DR_t.inverse());

}
