#include <fstream>
#include <cassert>
#include <iostream>
#include "DumpIO.hpp"

int DumpIO::NumDims(std::ifstream& read_dump)
{

	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	// Runs LoadHeader to obtain dimension information
	// then rewinds to the beginning of file
	assert(read_dump.is_open());
	if(!run_LoadHeader)
	{
		LoadHeader(read_dump);
		read_dump.clear();
		read_dump.seekg(std::ios::beg);
		current_f = -1;
	}

    return d;
}
