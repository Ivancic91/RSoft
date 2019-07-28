#include "DynamicMeasures.hpp"
#include "../MDTools/MDTools.hpp"
#include "../Eigen/Dense"
#include <iostream>


void DynamicMeasures::LambdaMin(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  int m,
  Eigen::MatrixXd& lambda_min_t)
{

  // Declares variables
  int n_p, d, n_neigh, neigh;
  std::vector<double> temp_vec, R_m_t, R_m_dt, R_neigh_t, R_neigh_dt;
  std::vector<double> dR_t_vec, dR_dt_vec;
  typedef Eigen::Matrix<double, -1, -1> Mat;
  typedef Eigen::Matrix<double, -1, -1> Vec;
  MDTools tool;

  // Initializes variables
  n_p = pos_t.size();
  temp_vec = pos_t[0];
  d = temp_vec.size();

  n_neigh = n_list_t[m].size();
  R_m_t = pos_t[m];
  R_m_dt = pos_dt[m];
  Mat DR_t_DR_t(d,d), DR_dt_DR_t(d,d);
  DR_t_DR_t.setZero();
  DR_dt_DR_t.setZero();

  // Finds DR_t_DR_t and DR_dt_DR_t matrices
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

    // Outer product X and Y
    DR_t_DR_t = DR_t_DR_t + dR_t*(dR_t.transpose());
    DR_dt_DR_t = DR_dt_DR_t + dR_dt*(dR_t.transpose());

  }

  lambda_min_t = DR_dt_DR_t*(DR_t_DR_t.inverse());

}
