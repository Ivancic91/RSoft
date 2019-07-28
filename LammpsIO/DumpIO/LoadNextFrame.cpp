#include <fstream>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::LoadNextFrame(std::ifstream& read_dump)
{

	bb_t.clear();
	pos_t.clear();
	id_t.clear();
	data_col_t.clear();

    LoadHeader(read_dump);
    if(!run_AnalyzeItemAtomsLine)
    {
    	AnalyzeItemAtomsLine(read_dump);
    }
    else
    {
    	std::string line;
    	std::getline(read_dump, line);
    }

    LoadAtomData(read_dump);
    current_f++;

    run_LoadNextFrame = true;

}
