#include "MDTools.hpp"
#include <assert.h>

void MDTools::InitializeCellDeltaArr(std::vector< std::vector<int> >& cell_delta_arr)
{
  assert(d==2 or d==3);
  std::vector<int> cell_pos;

  if(d==2)
  {
    for(int ii=-1; ii<2; ii++)
    {
      cell_pos.push_back(ii);
      cell_pos.push_back(1);
      cell_delta_arr.push_back(cell_pos);
      cell_pos.clear();
    }
    cell_pos.push_back(1);
    cell_pos.push_back(0);
    cell_delta_arr.push_back(cell_pos);

  }
  else
  {
    // Initializes delta_cell arr
    for(int ii = -1; ii<2; ii++)
    {
      for(int jj=-1; jj<2; jj++)
      {
        cell_pos.push_back(ii);
        cell_pos.push_back(jj);
        cell_pos.push_back(1);

        cell_delta_arr.push_back(cell_pos);
        cell_pos.clear();
      }
      cell_pos.push_back(ii);
      cell_pos.push_back(1);
      cell_pos.push_back(0);

      cell_delta_arr.push_back(cell_pos);
      cell_pos.clear();
    }
    cell_pos.push_back(1);
    cell_pos.push_back(0);
    cell_pos.push_back(0);

    cell_delta_arr.push_back(cell_pos);
    cell_pos.clear();
  }



}
