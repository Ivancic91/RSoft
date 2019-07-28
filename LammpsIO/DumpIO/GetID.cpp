#include <vector>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::GetID(std::vector<int>& id_t_)
{
	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	if(!found_id)
	{
		std::cout << "ERROR: no IDS found in file";
		assert(found_id);
	}
	else
	{
		id_t_ = id_t;
	}

}

