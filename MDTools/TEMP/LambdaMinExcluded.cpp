/*
#include "MDTools.hpp"
#include "../Eigen/Dense"
#include <iostream>


void MDTools::LambdaMinExcluded(
		std::vector< std::vector<double> >& pos_t,
		std::vector< std::vector<double> >& bb_t,
		std::vector< std::vector<double> >& pos_dt,
		std::vector< std::vector<double> >& bb_dt,
		std::vector<std::string>& bc,
		std::vector< std::vector<int> >& n_list_t,
		int m,
		Eigen::MatrixXd& lambda_min_t)
{
	// Defines global variables
	n_p = pos_t.size();
	d = 3;

	// Declares variables
	int n_neigh, neigh;
	double d_lambda, d_lambda_max;
	std::vector<double> temp_vec, R_m_t, R_m_dt, R_neigh_t, R_neigh_dt;
	std::vector<double> dR_t_vec, dR_dt_vec;
	Eigen::MatrixXd& lambda_min_temp, lambda_min_max;
	typedef Eigen::Matrix<double, -1, -1> Mat;
	typedef Eigen::Matrix<double, -1, -1> Vec;
	std::vector<Eigen::MatrixXd> dR_t_dR_t_vec, dR_dt_dR_t_vec;
    Mat X(d,d), Y(d,d);

    // Initializes variables
	n_neigh = n_list_t[m].size();
	d_lambda = 0, d_lambda_max = 0;
	R_m_t = pos_t[m];
    R_m_dt = pos_dt[m];
    X.setZero();
    Y.setZero();

    // Finds DR_t_DR_t and DR_dt_DR_t matrices
    for(int n=0; n<n_neigh; n++)
    {
    	// Calculates delta R vectors at time t and t + dt
    	neigh = n_list_t[m][n];
    	R_neigh_t = pos_t[neigh];
    	R_neigh_dt = pos_dt[neigh];
    	DeltaR(R_neigh_t, R_m_t, bb_t, bc, dR_t_vec);
    	DeltaR(R_neigh_dt, R_m_dt, bb_dt, bc, dR_dt_vec);

    	// Initializes Eigen vectors to do LA computations
        Eigen::Map<Vec> dR_t(dR_t_vec.data(), d, 1);
        Eigen::Map<Vec> dR_dt(dR_dt_vec.data(), d, 1);

        // Outer product X and Y Falk and Langer
        dR_dt_dR_t_vec.push_back(dR_dt*(dR_t.transpose()));
        X = X + dR_dt_dR_t_vec[n];
        dR_t_dR_t_vec.push_back(dR_t*(dR_t.transpose()));
        Y = Y + dR_t_dR_t_vec[n];

    }

    lambda_min_t = X*(Y.inverse());
    for(int n=0; n<n_neigh; n++)
    {
    	lambda_min_temp = (X-dR_dt_dR_t_vec[n])*((Y-dR_t_dR_t_vec[n]).inverse());
    	d_lambda = (((lambda_min_t-lambda_min_temp).array()).square()).sum();

    	if(d_lambda > d_lambda_max)
    	{
    		d_lambda_max = d_lambda;
    		lambda_min_max = lambda_min_temp;
    	}

    lambda_min_t = lambda_min_max;

    }

}
*/
