#include "MDTools.hpp"
#include "../Eigen/Dense"
#include <iostream>
#include <math.h>


void MDTools::CauchyStress(
		std::vector< std::vector<double> >& pos_t,
		std::vector< std::vector<double> >& bb_t,
		std::vector<std::string>& bc,
		std::vector< std::vector<int> >& n_list_t,
		double epsilon,
		double Delta,
		int m,
		Eigen::MatrixXd& stress_t)
{
	// Defines global variables
	n_p = pos_t.size();
	d = 3;

	// Declares variables
	int n_neigh, neigh;
	double force, r, r_m_Delta, r_m_Delta_3, r_m_Delta_6, r_m_Delta_13;
	std::vector<double> temp_vec, R_m_t, R_neigh_t;
	std::vector<double> dR_t_vec;
	typedef Eigen::Matrix<double, -1, -1> Mat;
	typedef Eigen::Matrix<double, -1, -1> Vec;
    Mat f_dR(d,d);

    // Initializes variables
	n_neigh = n_list_t[m].size();
	R_m_t = pos_t[m];
	f_dR.setZero();

    // Finds f*n^T matrix (cauchy stress)
    for(int n=0; n<n_neigh; n++)
    {
    	// Calculates delta R vectors at time t and t + dt
    	neigh = n_list_t[m][n];
    	R_neigh_t = pos_t[neigh];
    	DeltaR(R_neigh_t, R_m_t, bb_t, bc, dR_t_vec);

    	// Initializes Eigen vectors to do LA computations
        Eigen::Map<Vec> dR_t(dR_t_vec.data(), d, 1);
        r = dR_t.norm();

        // Computes force from neighbor
        r_m_Delta = r-Delta;
        r_m_Delta_3 = r_m_Delta*r_m_Delta*r_m_Delta;
        r_m_Delta_6 = r_m_Delta_3*r_m_Delta_3;
        r_m_Delta_13 = r_m_Delta_6*r_m_Delta_6*r_m_Delta;
        force = 24*epsilon*(r_m_Delta_6 - 2)/(r_m_Delta_13);

        // Outer product X and Y
        f_dR = f_dR + (force*dR_t)*(dR_t.transpose());

    }

    stress_t = f_dR;

}
