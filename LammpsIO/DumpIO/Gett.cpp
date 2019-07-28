#include <vector>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::Gett(int& t_)
{
	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	if(!found_timestep)
	{
		std::cout << "WARNING: Did not found timestep in dump file";
	}
	else
	{
		t_ = t;
	}

}

