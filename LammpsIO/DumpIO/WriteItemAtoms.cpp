#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::WriteItemAtoms(std::ofstream& write_dump)
{
	// Writes the header
	write_dump << "ITEM: ATOMS ";
	if(set_id)
	{
		write_dump << "id ";
	}
	if(d==2)
	{
		write_dump << "x y ";
	}
	else
	{
		write_dump << "x y z ";
	}
	for(int dc=0; dc<n_dc; dc++)
	{
		write_dump << data_cols_labels[dc] << " ";
	}
	write_dump << "\n";

	for(int p=0; p<n_p; p++)
	{
		// writes the id of each particle
		if(set_id)
		{
			write_dump << id_t[p] << " ";
		}

		// Writes location of each dimension
		for(int dd=0; dd<d; dd++)
		{
			write_dump << pos_t[p][dd] << " ";
		}

		// Writes data columns
		for(int dc=0; dc<n_dc; dc++)
		{
			write_dump << data_col_t[p][dc] << " ";
		}
		write_dump << "\n";
	}

}
