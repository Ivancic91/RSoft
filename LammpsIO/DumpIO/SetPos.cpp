#include "DumpIO.hpp"
#include <iostream>
#include <cassert>

void DumpIO::SetPos(std::vector< std::vector<double> >& pos_t_)
{

	if(run_input or !run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(!run_input or run_output);
	}


	pos_t = pos_t_;
	set_pos = true;

	if(set_id)
	{
		if(n_p!=pos_t_.size())
		{
			std::cout << "Number of particles mismatch!";
			assert(n_p==pos_t_.size());
		}
	}
	else
	{
		n_p = pos_t_.size();
	}

	if(set_bb)
	{
		if(d!=pos_t_[0].size())
		{
			std::cout << "Dimensions mismatch!";
			assert(d==pos_t_[0].size());
		}
	}
	else
	{
		d = pos_t_[0].size();
	}

}
