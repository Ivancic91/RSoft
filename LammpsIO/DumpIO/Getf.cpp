#include <vector>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::Getf(int& f_)
{

	if(!run_input or run_output)
	{
		std::cout << "ERROR: running input function after opening output";
		assert(run_input or !run_output);
	}
	f_ =  current_f;

}

