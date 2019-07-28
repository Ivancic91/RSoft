#include <vector>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::GetBB(std::vector< std::vector<double> >& bb_t_)
{
	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	bb_t_ =  bb_t;
}

