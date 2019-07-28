#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"
#include <math.h>
#include <assert.h>

void MDTools::BinParticlesIntoThetaCells(
		std::vector<double>& theta,
		double theta_c,
		std::vector< std::vector<int> >& particles_cell)
{
	int n_theta, cell_idx;
	double theta_cell_size, theta_p;
	std::vector<int> filler_vec;
	VectorTools vtool;

	// Determine cell size
	n_theta = int(2.*M_PI/theta_c);
	if(n_theta%2 != 0)
	{
		n_theta-=1;
	}
	theta_cell_size = 2.*M_PI/double(n_theta);

	// Initialize particles_cell
	vtool.Clear2DVec(particles_cell);
	for(int cell=0; cell<n_theta; cell++)
	{
		particles_cell.push_back(filler_vec);
	}

	// Place particles in cells
	for(int p=0; p<n_p; p++)
	{
		theta_p = theta[p];
		cell_idx = int(theta_p/theta_cell_size);
		particles_cell[cell_idx].push_back(p);
	}

}

