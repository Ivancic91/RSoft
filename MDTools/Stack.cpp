#include "MDTools.hpp"
#include <assert.h>

void MDTools::Stack(std::vector<double>& pos, std::vector<std::vector<double> >& bb_t, int& cell_idx)
{
  std::vector<int> cell_pos;
  for(int dd=0; dd<d; dd++)
  {
    cell_pos.push_back(int((pos[dd]-bb_t[dd][0])/cell_lengths[dd]));
  }
  Stack(cell_pos, cell_idx);
}

void MDTools::Stack(std::vector<int>& cell_pos, int& cell_idx)
{
  //assert(d==2 or d==3);

  if(d==2)
  {
    cell_idx = cell_pos[0]+cell_pos[1]*n_cells[0];
  }
  else
  {
    cell_idx = cell_pos[0]+(cell_pos[1]+cell_pos[2]*n_cells[1])*n_cells[0];
  }

}
