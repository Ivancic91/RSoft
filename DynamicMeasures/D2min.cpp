#include "DynamicMeasures.hpp"
#include "../MDTools/MDTools.hpp"
#include <vector>
#include "../Eigen/Dense"
#include <iostream>


void DynamicMeasures::D2min(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  int& m,
  double& d2min)
{

  // Declares variables
  int n_neigh, neigh, d;
  Eigen::MatrixXd lambda_min_t;
  std::vector<double> temp_vec, R_m_t, R_m_dt, R_neigh_t, R_neigh_dt;
  std::vector<double> dR_t_vec, dR_dt_vec;
  typedef Eigen::Matrix<double, -1, -1> Vec;
  MDTools tool;

  // Initializes variables
  d2min = 0;
  n_neigh = n_list_t[m].size();
  R_m_t = pos_t[m];
  R_m_dt = pos_dt[m];
  d = pos_t[m].size();
  LambdaMin(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, m, lambda_min_t);

  for(int n=0; n<n_neigh; n++)
  {
    // Calculates delta R vectors at time t and t + dt
    neigh = n_list_t[m][n];
    R_neigh_t = pos_t[neigh];
    R_neigh_dt = pos_dt[neigh];
    tool.DeltaR(R_neigh_t, R_m_t, bb_t, bc, dR_t_vec);
    tool.DeltaR(R_neigh_dt, R_m_dt, bb_dt, bc, dR_dt_vec);

    // Initializes Eigen vectors to do LA computations
    Eigen::Map<Vec> dR_t(dR_t_vec.data(), d, 1);
    Eigen::Map<Vec> dR_dt(dR_dt_vec.data(), d, 1);

    d2min += (dR_dt-lambda_min_t*dR_t).array().square().sum();
  }

  d2min = d2min/double(n_neigh);

}
