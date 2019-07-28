#define _USE_MATH_DEFINES
#include <cmath>
#include "DynamicMeasures.hpp"
#include <vector>
#include <iostream>
#include "../Eigen/Dense"


void DynamicMeasures::J2plane(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  double theta,
  double phi,
  int& m,
  double& j2)
{

  // Declares variables
  std::vector<double> temp = pos_t[0];
  int d = temp.size();
  double n_invariant;
  double temp_double;
  Eigen::MatrixXd lambda_min_t, n, diff, nmat, smat;
  Eigen::VectorXd nvec(d), svec(d);

  if(d==3)
  {
    nvec(0) = sin(phi)*cos(theta);
    nvec(1) = sin(phi)*sin(theta);
    nvec(2) = cos(phi);
    svec(0) = sin(phi-M_PI_2)*cos(theta);
    svec(1) = sin(phi-M_PI_2)*sin(theta);
    svec(2) = cos(phi-M_PI_2);
  }
  else
  {
    // Assumes dimension = 2
    nvec(0) = sin(theta);
    nvec(1) = cos(theta);
    svec(0) = sin(theta-M_PI_2);
    svec(1) = cos(theta-M_PI_2);
  }


  // Initializes variables
  LambdaMin(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, m, lambda_min_t);
  
  // J2 calculation
  nmat = nvec*(nvec.transpose());
  smat = svec*(svec.transpose());
  lambda_min_t = (smat.transpose())*lambda_min_t*nmat;

  n = 0.5*((lambda_min_t.transpose())*lambda_min_t - 
        Eigen::MatrixXd::Identity(d,d));
  n_invariant = n.trace()/d;
  diff = n - n_invariant*Eigen::MatrixXd::Identity(d,d);

  // Calculates j2
  temp_double = 0.5*((diff.array()).square()).sum();
  j2 = sqrt(temp_double);

}
