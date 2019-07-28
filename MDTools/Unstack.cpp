#include "MDTools.hpp"
#include <assert.h>

void MDTools::Unstack(int& cell_idx, std::vector<int>& cell_pos)
{
  assert(d==2 or d==3);
  cell_pos.clear();

  if(d==2)
  {
    int x, y, n_x = n_cells[0];

    y = cell_idx/(n_x);
    x = cell_idx-y*n_x;

    cell_pos.push_back(x);
    cell_pos.push_back(y);
  }
  else
  {
    int x, y, z, n_x = n_cells[0], n_y = n_cells[1];

    z = cell_idx/(n_x*n_y);
    y = (cell_idx-z*n_x*n_y)/n_x;
    x = cell_idx-z*n_x*n_y-y*n_x;

    cell_pos.push_back(x);
    cell_pos.push_back(y);
    cell_pos.push_back(z);
  }

}
