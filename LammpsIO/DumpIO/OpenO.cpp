#include <fstream>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::OpenO(std::ofstream& write_dump)
{
	// opens dump to check if it exists
    if ( !write_dump.is_open() )
    {
    	std::cout << "\n\nFile did not open.\n\n";
    	assert(write_dump.is_open());
    }
    else
    {
    	InitializeWriteParameters();
    }
}
