#include "MDTools.hpp"
#include <math.h>
#include <assert.h>

void MDTools::AddNeighborsTheta(
		std::vector<double>& theta,
		std::vector< std::vector<int> >& particles_cell,
		double theta_c,
		int cell_idx,
		int neigh_cell_idx,
		int lambda,
		std::vector< std::vector<int> >& n_list)
{
	assert(lambda==1 or lambda==-1);
	int n_p_cell = particles_cell[cell_idx].size();
	int n_p_neigh_cell = particles_cell[neigh_cell_idx].size();
	int p, p_neigh;
	double theta_p, theta_p_neigh, theta_diff, shift;
	double Tau = 2.*M_PI;

	// Determines shift
	if(lambda==1)
	{
		shift = 0;
	}
	else
	{
		shift = M_PI;
	}

	for(int p_cell=0; p_cell<n_p_cell; p_cell++)
	{
		p = particles_cell[cell_idx][p_cell];
		theta_p = theta[p];
		if(cell_idx==neigh_cell_idx)
		{
			n_p_neigh_cell = p_cell;
		}

		for(int p_neigh_cell=0; p_neigh_cell<n_p_neigh_cell; p_neigh_cell++)
		{
			p_neigh = particles_cell[neigh_cell_idx][p_neigh_cell];
			theta_p_neigh = theta[p_neigh];

			theta_diff = fabs(theta_p_neigh-theta_p-shift);
			theta_diff = fmod(theta_diff, Tau);

			if(theta_diff < theta_c)
			{
				n_list[p].push_back(p_neigh);
				n_list[p_neigh].push_back(p);
			}

		}
	}
}
