#include "MDTools.hpp"
#include <vector>
#include <iostream>
#include "../Eigen/Dense"


void MDTools::J2Stress(
		std::vector< std::vector<double> >& pos_t,
		std::vector< std::vector<double> >& bb_t,
		std::vector<std::string>& bc,
		std::vector< std::vector<int> >& n_list_t,
		double epsilon,
		double Delta,
		int& m,
		double& j2)
{

	// Declares variables
	std::vector<double> temp = pos_t[0];
	int d = temp.size();
	double n_invariant;
	double temp_double;
	Eigen::MatrixXd stress_t, n, diff;
	Eigen::Matrix<double, 3, 3> I = Eigen::Matrix<double, 3, 3>::Identity();

    // Initializes variables
	CauchyStress(pos_t, bb_t, bc, n_list_t, epsilon, Delta, m, stress_t);

	// J2 calculation
	n = 0.5*((stress_t.transpose())*stress_t - I);
	n_invariant = n.trace()/d;
	diff = n - n_invariant*I;

	// Calculates j2
	temp_double = 0.5*((diff.array()).square()).sum();
	j2 = sqrt(temp_double);



}
