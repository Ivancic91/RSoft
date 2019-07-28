#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::LoadAtomData(std::ifstream& read_dump)
{

	int idx, curr_dc, n_col;
	std::string line = "";
	std::string elem = "";
	std::vector<double> pos_t_i (d);
	std::vector<double> dc_t_i (n_dc);
	bool x_here, y_here, z_here, id_here;

	// Finds # of columns
	n_col = d + n_dc;
	if(found_id)
	{
		n_col += 1;
	}

	for(int p=0; p<n_p; p++)
	{
		std::getline(read_dump, line);
		idx = 0;
		curr_dc = 0;
		x_here = false, y_here = false, z_here = false, id_here = false;

		for(int col=0; col<n_col; col++)
		{
			idx = NextElem(line, idx, elem);
			if(elem.empty())
			{
				std::cout << "ERROR: line unreadable\n";
				assert(!elem.empty());
			}
			else if(elem.find("ITEM:")!=std::string::npos)
			{
				std::cout << "ERROR: missing line\n";
				assert(elem.find("ITEM:")==std::string::npos);
			}
			else
			{
				if(col==col_x)
				{
					pos_t_i[0] = atof(elem.c_str());
					x_here = true;
				}
				else if(col==col_y)
				{
					pos_t_i[1] = atof(elem.c_str());
					y_here = true;
				}
				else if(col==col_z)
				{
					pos_t_i[2] = atof(elem.c_str());
					z_here = true;
				}
				else if(col==col_id)
				{
					id_t.push_back(atoi(elem.c_str()));
					id_here = true;
				}
				else
				{

					if(!found_data_col or curr_dc>=n_dc)
					{
						std::cout << d <<"\n";
						std::cout << n_dc<<"\n";
						std::cout << col_z<<"\n";
						std::cout << "ERROR: Found extra data column\n";
						assert(curr_dc <= n_dc);
					}
					else
					{
						dc_t_i[curr_dc] = atof(elem.c_str());
						curr_dc += 1;
					}

				}
			}
		}


		// Checking for errors on line
		if(d==2)
		{
			if(!(x_here and y_here))
			{
				std::cout << "ERROR: x or y coordinate for particle not found\n";
				assert(x_here and y_here);
			}
		}
		else
		{
			if(!(x_here and y_here and z_here))
			{
				std::cout << "ERROR: x, y, or z coordinate for particle not found\n";
				assert(x_here and y_here and z_here);
			}
		}
		if(id_here!=found_id)
		{
			std::cout << "ERROR: id's found but not listed\n";
			assert(id_here==found_id);
		}
		if(n_dc!=curr_dc)
		{
			std::cout << "ERROR: data column not found\n";
			assert(n_dc==curr_dc);
		}


		data_col_t.push_back(dc_t_i);
		pos_t.push_back(pos_t_i);


	}
}
