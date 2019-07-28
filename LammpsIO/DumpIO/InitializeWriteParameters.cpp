#include "DumpIO.hpp"
#include <iostream>


void DumpIO::InitializeWriteParameters()
{

	// Resets dimensions to -1 to flag they have
	// not been set
	d = -1;
	n_f = -1;
	n_dc = 0;
	n_p = -1;

	// Sets set variables to false to indicate these
	// variables have not been set
	set_t = false;
	set_bb = false;
	set_id = false;
	set_pos = false;
	set_dc = false;

	// Clears out box boundary, position and id vectors
	// to ensure no future issues
	bb_t.clear();
	pos_t.clear();
	id_t.clear();
	data_col_t.clear();
	data_cols_labels.clear();

	//std::cout << "DC size: " << data_col_t.size() <<"--\n";
	//std::cout << "DC row size: " << data_col_t[0].size() << "--\n";

	/*
	std::cout << "DC size: " << data_col_t.size() <<"--\n";
	if(data_col_t.size()>0)
	{
		data_cols_labels.clear();
		for(int p=0; p<n_p; p++)
		{
			data_col_t[p].clear();
		}
		data_col_t.clear();
	}
	*/

	// Indicates running output functions
	run_output = true;
	run_input = false;

}
