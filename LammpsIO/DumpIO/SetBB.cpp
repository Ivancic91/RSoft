#include "DumpIO.hpp"
#include <vector>
#include <iostream>
#include <cassert>

void DumpIO::SetBB( std::vector< std::vector<double> >& bb_t_)
{

	if(run_input or !run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(!run_input or run_output);
	}

	bb_t = bb_t_;
	set_bb = true;

	if(set_pos)
	{
		if(d!=bb_t_.size())
		{
			std::cout << "ERROR: dimensions mismatch\n";
			assert(d==bb_t_.size());
		}
	}
	else
	{
		d = bb_t_.size();
	}
}
