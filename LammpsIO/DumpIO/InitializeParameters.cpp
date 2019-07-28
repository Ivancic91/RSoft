#include "DumpIO.hpp"
#include <iostream>

void DumpIO::InitializeParameters()
{

	// Has not run these functions
	run_LoadHeader = false;
	run_AnalyzeItemAtomsLine = false;
	run_LoadNextFrame = false;

	// Has not found these variables
	found_id = false;
	found_timestep = false;
	found_data_col = false;
	found_num_parts = false;

	// Resets dimensions to -1 to flag they have
	// not been set
	d = -1;
	n_f = -1;
	n_dc = 0;
	n_p = -1;
	t = -1;
	current_f = 0;
	col_x = -1;
	col_y = -1;
	col_z = -1;
	col_id = -1;

	// Clears out box boundary, position and id vectors
	// to ensure no future issues
	bb_t.clear();
	pos_t.clear();
	id_t.clear();
	data_col_t.clear();
        data_cols_labels.clear();

	// Indicates running output functions
	run_output = false;
	run_input = true;



}

