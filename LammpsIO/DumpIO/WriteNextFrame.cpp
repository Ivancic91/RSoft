#include <fstream>

#include <vector>
#include <string>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::WriteNextFrame(std::ofstream& write_dump)
{
	// Makes sure necessary sets have been run
	if(!(set_t and set_bb and set_pos))
	{
		std::cout << "ERROR: Must set:\n";
		std::cout << "    1) timestep\n";
		std::cout << "    2) box boundary\n";
		std::cout << "    3) positions\n";
	}

	write_dump << "ITEM: TIMESTEP\n";
	write_dump << t << "\n";
	write_dump << "ITEM: NUMBER OF ATOMS\n";
	write_dump << n_p << "\n";
	write_dump << "ITEM: BOX BOUNDS\n";
	for(int dd=0; dd<d; dd++)
	{
		write_dump << bb_t[dd][0] << " " << bb_t[dd][1] << "\n";
	}

	WriteItemAtoms(write_dump);
	InitializeWriteParameters();

}
