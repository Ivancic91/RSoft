#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::GetDataCol(std::string label, std::vector<double>& data_t_)
{
  int dc_col = -1;
  data_t_.clear();

  if(!run_input or run_output)
  {
    std::cout << "ERROR: running input function after opening output";
    assert(run_input or !run_output);
  }
  if(!found_data_col)
  {
    std::cout << "WARNING: no data column found";
  }
  else
  {
    // Finds data column
    for(int dc = 0; dc<n_dc; dc++)
    {
      if(label.compare(data_cols_labels[dc]) == 0)
      {
        dc_col = dc;
      }
    }

    // Gets data from column
    if(dc_col == -1)
    {
      std::cout << "WARNING: could not find data column \n";
    }
    else
    {
      for(int p=0; p<n_p; p++)
      {
        data_t_.push_back(data_col_t[p][dc_col]);
      }
    }
  }

}

void DumpIO::GetDataCol(std::string label, std::vector<int>& data_t_)
{
  int dc_col = -1;
  data_t_.clear();

  if(!run_input or run_output)
  {
    std::cout << "ERROR: running input function after opening output";
    assert(run_input or !run_output);
  }
  if(!found_data_col)
  {
    std::cout << "WARNING: no data column found";
  }
  else
  {
    // Finds data column
    for(int dc = 0; dc<n_dc; dc++)
    {
      if(label.compare(data_cols_labels[dc]) == 0)
      {
        dc_col = dc;
      }
    }

    // Gets data from column converts to ints
    if(dc_col == -1)
    {
      std::cout << "WARNING: could not find data column \n";
    }
    else
    {
      for(int p=0; p<n_p; p++)
      {
        data_t_.push_back(((int) data_col_t[p][dc_col]));
      }
    }
  }

}

