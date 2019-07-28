#include <cassert>
#include <string>
#include <iostream>
#include "MDTools.hpp"

bool MDTools::AddCellPos(
      std::vector<int>& cell_pos,
      std::vector<int>& cell_delta,
      std::vector< std::vector<double> >& bb_t,
      std::vector<std::string>& bc,
      std::vector<int>& neigh_cell_pos,
      std::vector<double>& shift)
{
  bool are_neighbors = true;
  std::string bc_dd;
  neigh_cell_pos.clear();
  shift.clear();

  for(int dd=0; dd<d; dd++)
  {
    neigh_cell_pos.push_back(cell_pos[dd]+cell_delta[dd]);
    bc_dd = bc[dd];
    if(bc_dd.compare("p") == 0)
    {
      if(neigh_cell_pos[dd]==-1)
      {
        neigh_cell_pos[dd] = n_cells[dd]-1;
        shift.push_back(bb_t[dd][0]-bb_t[dd][1]);
      }
      else if(neigh_cell_pos[dd]==n_cells[dd])
      {
        neigh_cell_pos[dd] = 0;
	shift.push_back(bb_t[dd][1]-bb_t[dd][0]);
      }
      else
      {
        shift.push_back(0);
      }
    }
    else
    {
      if(neigh_cell_pos[dd]==-1 or neigh_cell_pos[dd]==n_cells[dd])
      {
        are_neighbors = false;
      }
      shift.push_back(0);
    }

    assert(neigh_cell_pos[dd] >= -1);
    assert(neigh_cell_pos[dd] <= n_cells[dd]);
  }

  return are_neighbors;
}
