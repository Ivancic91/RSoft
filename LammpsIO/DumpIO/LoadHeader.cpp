#include <fstream>
#include <vector>
#include <string>
#include <cassert>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::LoadHeader(std::ifstream& read_dump)
{
	// Checks for initialization
	if(run_output or !run_input)
	{
		std::cout << "ERROR: Must run OpenI or OpenO to initialize\n";
		assert(!run_output);
		assert(run_input);
	}

	std::vector<double> bb_t_i (2);
	std::streampos prev_line;
	int idx = 0;
	d = 0;
	std::string line = "";
	std::string elem = "";
	found_timestep = false;
	found_num_parts = false;
	found_box_bounds = false;

	while(line.find("ITEM: ATOMS")==std::string::npos)
	{
		prev_line = read_dump.tellg();
		std::getline(read_dump, line);

		if(line.find("ITEM: TIMESTEP")!=std::string::npos)
		{
			// Gets time step
			std::getline(read_dump, line);
			t = atoi(line.c_str());
			found_timestep = true;
		}
		if(line.find("ITEM: NUMBER OF ATOMS")!=std::string::npos)
		{
			// Gets number of particles
			std::getline(read_dump, line);
			n_p = atoi(line.c_str());
			found_num_parts = true;
		}
		if(line.find("ITEM: BOX BOUNDS")!=std::string::npos)
		{
			// Gets data from boundary conditions
			std::getline(read_dump, line);
			while(line.find("ITEM:")==std::string::npos)
			{
				d++;
				idx = 0;
				idx = NextElem(line, idx, elem);
				bb_t_i[0] = atof(elem.c_str());
				idx = NextElem(line, idx, elem);
				bb_t_i[1] = atof(elem.c_str());
				bb_t.push_back(bb_t_i);

				prev_line = read_dump.tellg();
				std::getline(read_dump, line);
			}
			// Ensures no ITEM: is skipped
			read_dump.seekg(prev_line);
			found_box_bounds = true;
		}
	}
	// Leaves file on line right before ITEM: ATOMS
	read_dump.seekg(prev_line);

    if(!found_num_parts)
    {
    	std::cout << "ERROR: Number of particles not found";
    	assert(found_num_parts);
    }
    if(!found_box_bounds)
    {
    	std::cout << "ERROR: Box boundaries not found";
    	assert(found_num_parts);
    }

	// Flags LoadHeader as having run
	run_LoadHeader = true;


}




