#include "MDTools.hpp"
#include <iostream>

void MDTools::AddNeighbors(
      std::vector< std::vector<double> >& pos_t,
      std::vector< std::vector<int> >& particles_cell,
      double R_c,
      std::vector<double> shift,
      int cell_idx,
      int neigh_cell_idx,
      std::vector< std::vector<int> >& n_list_t)
{
  // Declares/initializes variables
  int n_p_cell = particles_cell[cell_idx].size();
  int n_p_neigh_cell = particles_cell[neigh_cell_idx].size();
  int p, p_neigh;
  double R_c_2 = R_c*R_c;
  double cell_coor, cell_neigh_coor, sq_sum;

  // Finds neighbors
  for(int p_cell=0; p_cell<n_p_cell; p_cell++)
  {
    // Particle index
    p = particles_cell[cell_idx][p_cell];

    // Ensures no double counting
    if(cell_idx == neigh_cell_idx)
    {
      n_p_neigh_cell = p_cell;
    }

    for(int p_neigh_cell=0; p_neigh_cell<n_p_neigh_cell; p_neigh_cell++)
    {
      // Neighboring Particle index
      p_neigh = particles_cell[neigh_cell_idx][p_neigh_cell];

      sq_sum = 0;
      for(int dd=0; dd<d; dd++)
      {
        cell_coor = pos_t[p][dd];
        cell_neigh_coor = pos_t[p_neigh][dd];

        // square difference accounting for PBCs
        sq_sum += (cell_coor-(cell_neigh_coor+shift[dd]))*
              (cell_coor-(cell_neigh_coor+shift[dd]));
      }

      if(sq_sum<R_c_2)
      {
        n_list_t[p].push_back(p_neigh);
        n_list_t[p_neigh].push_back(p);
      }

    }

  }

}
