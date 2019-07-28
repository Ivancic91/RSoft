#include <vector>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::GetPos(std::vector< std::vector<double> >& pos_t_)
{

	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}

	pos_t_ =  pos_t;
}

