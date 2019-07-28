#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::GetDataColLabels(std::vector<std::string>& data_cols_labels_)
{
	if(!found_data_col)
	{
		std::cout << "WARNING: no data column found";
	}
	else
	{
		data_cols_labels_ =  data_cols_labels;
	}
	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

}
