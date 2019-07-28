#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"
#include <iostream>

void MDTools::GetNList(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  double R_c,
  std::vector< std::vector<int> >& n_list_t)
{

  // Declares variables
  VectorTools vtool;
  bool are_neighbors;
  int n_cells_tot, neigh_cell_idx;
  std::vector<int> cell_pos, cell_delta, neigh_cell_pos, filler_vec;
  std::vector<double> shift = pos_t[0];
  std::vector< std::vector<int> > cell_delta_arr;
  std::vector< std::vector<int> > particles_cell;

  // Initializes variables
  n_p = pos_t.size();
  d = shift.size();
  vtool.Clear2DVec(n_list_t);
  InitializeCellDeltaArr(cell_delta_arr);

	// Initialize n_list
	for(int p=0; p<n_p; p++)
	{
		n_list_t.push_back(filler_vec);
	}


	// Bins Particles into cells
	BinParticlesIntoCells(pos_t, bb_t, R_c, particles_cell);
	n_cells_tot = particles_cell.size();


	// Adds Neighbors
	for(int cell_idx=0; cell_idx<n_cells_tot; cell_idx++)
	{
		// Initializes shift
		for(int dd=0; dd<d; dd++)
		{
			shift[dd] = 0;
		}

		AddNeighbors(pos_t, particles_cell, R_c, shift, cell_idx, cell_idx, n_list_t);
		Unstack(cell_idx, cell_pos);

		for(int cd_idx=0; cd_idx<cell_delta_arr.size(); cd_idx++)
		{
			// neigh_cell_pos = cell_pos + cell_delta w/ periodic bc condition possibility
			cell_delta = cell_delta_arr[cd_idx];
			are_neighbors = AddCellPos(cell_pos, cell_delta, bb_t, bc, neigh_cell_pos, shift);
			Stack(neigh_cell_pos, neigh_cell_idx);

			if(are_neighbors)
			{
				AddNeighbors(pos_t, particles_cell, R_c, shift,
						cell_idx, neigh_cell_idx, n_list_t);
			}

		}


	}


	vtool.Clear2DVec(particles_cell);


}
