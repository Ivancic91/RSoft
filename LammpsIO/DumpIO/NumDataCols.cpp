#include <fstream>
#include <cassert>
#include <iostream>
#include "DumpIO.hpp"

int DumpIO::NumDataCols(std::ifstream& read_dump){

	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	current_f = -1;

	if(!run_AnalyzeItemAtomsLine)
	{
		//Rewind to the beginning
		read_dump.clear();
		read_dump.seekg(std::ios::beg);
		LoadHeader(read_dump);
		AnalyzeItemAtomsLine(read_dump);
	}

	// Rewind to the beginning
	read_dump.clear();
	read_dump.seekg(std::ios::beg);

	return n_dc;
}
