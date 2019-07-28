#include "MDTools.hpp"

void MDTools::BinParticlesIntoCellsPub(
		std::vector< std::vector<double> >& pos_t,
		std::vector< std::vector<double> >& bb_t,
		double R_c,
		std::vector< std::vector<int> >& particles_cell)
{

        // Declares variables
        std::vector<double> shift = pos_t[0];

        // Initializes variables
        n_p = pos_t.size();
        d = shift.size();

	// Initialize parameters
	int n_cells_tot, cell_idx;
	double L;
	std::vector<double> pos;
	std::vector<int> filler_vec;
	particles_cell.clear();
	n_cells.clear();
	cell_lengths.clear();

	// Determine cell size
	for(int dd=0; dd<d; dd++)
	{
		L = bb_t[dd][1] - bb_t[dd][0];

		// number of cells
		n_cells.push_back(int(L/R_c));
		if(n_cells[dd] < 3)
		{
			n_cells[dd] = 3;
		}

		// length of each cell dimension
		cell_lengths.push_back(L/double(n_cells[dd]));
	}

	// Reserve space for particles_cell
	n_cells_tot = 1;
	for(int dd=0; dd<d; dd++)
	{
		n_cells_tot *= n_cells[dd];
	}

	// Initialize particles_cell
	for(int cell=0; cell<n_cells_tot; cell++)
	{
		particles_cell.push_back(filler_vec);
	}

	// Place particles in cells
	for(int p=0; p<n_p; p++)
	{
		pos = pos_t[p];
		Stack(pos, bb_t, cell_idx);
		particles_cell[cell_idx].push_back(p);
	}
}
