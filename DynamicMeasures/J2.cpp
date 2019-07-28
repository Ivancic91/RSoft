#include "DynamicMeasures.hpp"
#include <vector>
#include <iostream>
#include "../Eigen/Dense"


void DynamicMeasures::J2(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  int& m,
  double& j2)
{

  // Declares variables
  std::vector<double> temp = pos_t[0];
  int d = temp.size();
  double n_invariant;
  double temp_double;
  Eigen::MatrixXd lambda_min_t, n, diff;

  // Initializes variables
  LambdaMin(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, m, lambda_min_t);

  // J2 calculation
  n = 0.5*((lambda_min_t.transpose())*lambda_min_t - 
        Eigen::MatrixXd::Identity(d,d));
  n_invariant = n.trace()/d;
  diff = n - n_invariant*Eigen::MatrixXd::Identity(d,d);

  // Calculates j2
  temp_double = 0.5*((diff.array()).square()).sum();
  j2 = sqrt(temp_double);

}
