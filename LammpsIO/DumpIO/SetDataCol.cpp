#include "DumpIO.hpp"
#include <vector>
#include <iostream>
#include <cassert>

void DumpIO::SetDataCol(std::string label, std::vector<double>& data_t_)
{

	if(run_input or !run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(!run_input or run_output);
	}

	if(set_pos)
	{
		if(n_p!=data_t_.size())
		{
			std::cout << "ERROR: dimensions mismatch";
			assert(n_p==data_t_.size());
		}
	}

	data_cols_labels.push_back(label);
	if(!set_dc)
	{
		std::vector<double> temp;

		for(int p=0; p<n_p; p++)
		{
			temp.push_back(data_t_[p]);
			data_col_t.push_back(temp);
			temp.clear();
		}
	}
	else
	{
		for(int p=0; p<n_p; p++)
		{
			data_col_t[p].push_back(data_t_[p]);
		}
	}

	set_dc = true;
	n_dc++;

}

void DumpIO::SetDataCol(std::string label, std::vector<int>& data_t_)
{
  std::vector<double> data_double(data_t_.begin(), data_t_.end());
  SetDataCol(label, data_double);
}
