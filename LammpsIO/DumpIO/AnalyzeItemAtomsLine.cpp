#include <fstream>
#include <string>
#include <cassert>
#include <vector>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::AnalyzeItemAtomsLine(std::ifstream& read_dump)
{
	// Checks for initialization
	if(run_output or !run_input)
	{
		std::cout << "ERROR: Must run OpenI or OpenO to initialize\n";
		assert(!run_output);
		assert(run_input);
	}

	bool x_here = false, y_here = false, z_here = false;

	int idx = 11; //Starts here to avoid 'ITEM: ATOMS'
	int col = 0;
	std::string line;
	std::string elem;
	std::getline(read_dump, line);

	// Gets dimension information if not present
	// Makes sure we are on correct line
	if(!run_LoadHeader)
	{
		LoadHeader(read_dump);
	}

	while( idx != -1)
	{
		idx = NextElem(line, idx, elem);

		if(elem.compare("x")==0)
		{
			col_x = col;
			x_here = true;
		}
		else if(elem.compare("y")==0)
		{
			col_y = col;
			y_here = true;
		}
		else if(elem.compare("z")==0)
		{
			col_z = col;
			z_here = true;

			if(d!=3)
			{
				std::cout << "ERROR: z label found but 2D data detected.";
				assert(d==3);
			}
		}
		else if(elem.compare("id")==0)
		{
			col_id = col;
			found_id = true;
		}
		else
		{
			if(!elem.empty())
			{
				data_cols_labels.push_back(elem);
				n_dc++;
				found_data_col = true;
			}
		}
		col++;
	}

	if(!(x_here and y_here))
	{
		std::cout << "ERROR: x or y label not found.";
		assert(x_here and y_here);
	}
	if(!z_here and d==3)
	{
		std::cout << "ERROR: z label not found but 3D data detected.";
		assert(z_here);
	}


	n_dc = data_cols_labels.size();
	run_AnalyzeItemAtomsLine = true;
}

