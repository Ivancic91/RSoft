#include "DumpIO.hpp"
#include <cassert>
#include <iostream>


void DumpIO::SortByID()
{
	if(!run_LoadNextFrame)
	{
		std::cout << "ERROR: Must load a frame before sorting";
		assert(run_LoadNextFrame);
	}
	if(!found_id)
	{
		std::cout << "WARNING: can only sort positions with IDs";
	}
	else
	{

		std::vector<int> id_t_sorted(n_p);
		std::vector< std::vector<double> > pos_t_sorted(n_p, std::vector<double>(d));
		std::vector< std::vector<double> > data_col_t_sorted(n_p, std::vector<double>(n_dc));

		for(int p=0; p<n_p; p++)
		{
			id_t_sorted[id_t[p]-1] = id_t[p];
			pos_t_sorted[id_t[p]-1] = pos_t[p];
			if(found_data_col)
			{
				data_col_t_sorted[id_t[p]-1] = data_col_t[p];
			}
		}

		id_t = id_t_sorted;
		pos_t = pos_t_sorted;
		if(found_data_col)
		{
			data_col_t = data_col_t_sorted;
		}
	}

}
