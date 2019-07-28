#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"
#include <iostream>

void MDTools::GetNListTheta(
		std::vector< std::vector<double> >& pos,
		double theta_c,
		std::vector< std::vector<int> >& n_list_lambda_p_1,
		std::vector< std::vector<int> >& n_list_lambda_m_1)
{
	// Declares variables
	VectorTools vtool;
	int neigh_cell_idx, n_cells_tot;
	std::vector< std::vector<int> > particles_cell;
	std::vector<int> filler_vec;
	std::vector<double> theta;

	// Initializes variables
	n_p = pos.size();
	vtool.Clear2DVec(n_list_lambda_p_1);
	vtool.Clear2DVec(n_list_lambda_m_1);

	// Initialize n_list
	for(int p=0; p<n_p; p++)
	{
		n_list_lambda_p_1.push_back(filler_vec);
		n_list_lambda_m_1.push_back(filler_vec);
	}

	// Bins Particles into cells
	CalculateTheta(pos, theta);
	BinParticlesIntoThetaCells(theta, theta_c, particles_cell);
	n_cells_tot = particles_cell.size(); // ENSURED TO BE EVEN!
	if(n_cells_tot<4)
	{
		std::cout << "ERROR: choose larger zeta or theta neighbor list is ineffective\n" << std::flush;
		std::cout << "theta_cut = " << theta_c << "\n" << std::flush;
		assert(n_cells_tot>=4);
	}

	// Adds neighbors for lambda+1
	for(int cell_idx=0; cell_idx<n_cells_tot; cell_idx++)
	{
		AddNeighborsTheta(theta, particles_cell, theta_c, cell_idx, cell_idx, 1, n_list_lambda_p_1);
		neigh_cell_idx = cell_idx+1;
		if(neigh_cell_idx >= n_cells_tot)
		{
			neigh_cell_idx = 0;
		}
		AddNeighborsTheta(theta, particles_cell, theta_c, cell_idx, neigh_cell_idx, 1, n_list_lambda_p_1);
	}

	// Adds neighbors for lambda-1
	for(int cell_idx=0; cell_idx<n_cells_tot/2; cell_idx++)
	{
		neigh_cell_idx = cell_idx+n_cells_tot/2-1;
		AddNeighborsTheta(theta, particles_cell, theta_c, cell_idx, neigh_cell_idx, -1, n_list_lambda_m_1);
		neigh_cell_idx = cell_idx+n_cells_tot/2;
		AddNeighborsTheta(theta, particles_cell, theta_c, cell_idx, neigh_cell_idx, -1, n_list_lambda_m_1);
		neigh_cell_idx = cell_idx+n_cells_tot/2+1;
		AddNeighborsTheta(theta, particles_cell, theta_c, cell_idx, neigh_cell_idx, -1, n_list_lambda_m_1);
	}
	if(n_cells_tot==4)
	{
		// Catches neighbor on same side
		AddNeighborsTheta(theta, particles_cell, theta_c, 2, 3, -1, n_list_lambda_m_1);
	}



}
