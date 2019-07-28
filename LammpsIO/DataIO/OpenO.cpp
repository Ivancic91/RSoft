#include <fstream>
#include <iostream>
#include <cassert>
#include "DataIO.hpp"

void DataIO::OpenO(std::ofstream& write_dump)
{
    // Checks order of functions is correct before and after
    // modifying function tag
    StatementOrderError();
    if( openO )
    {
        std::cout << "ERROR: Cannot open output twice in same instance\n";
        std::cout << std::flush;
        assert(not openO);
    }
    openO = true;
    StatementOrderError();

    // opens dump to check if it exists
    if ( !write_dump.is_open() )
    {
    	std::cout << "ERROR: File did not open\n";
    	assert(write_dump.is_open());
    }
}
