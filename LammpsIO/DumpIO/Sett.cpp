#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::Sett(int t_)
{
	if(run_input or !run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(!run_input or run_output);
	}


	t = t_;
	set_t = true;
}
