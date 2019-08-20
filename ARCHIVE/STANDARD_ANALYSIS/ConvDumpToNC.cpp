#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include "LammpsIO/NetCDFIO/NetCDFIO.hpp"
#include "LammpsIO/DumpIO/DumpIO.hpp"


int main(int argc, char* argv[])
{
    std::string dump_file_str, nc_file_str;
    int d, n_f, n_p, t;
    std::vector< std::vector<double> > bb_t;
    std::vector< std::vector<double> > pos_t;

    if(argc!=3)
    {
        std::cout << "INPUT FORM: './DumpToNc [dumpfile] [ncfile]'";
        assert(argc==3);
    }
    else
    {
        dump_file_str = argv[1];
        nc_file_str = argv[2];
    }

    // Creates DumpIO objects for reading and writing
    std::ifstream read_file(dump_file_str.c_str());
    DumpIO dumpfile;
    dumpfile.OpenI(read_file);

    NetCDFIO ncfile;
    ncfile.OpenO(nc_file_str);

    d = dumpfile.NumDims(read_file);
    n_f = dumpfile.NumFrames(read_file);
    n_p = dumpfile.NumPartsCurrentf(read_file);

    // Prints out parameters read from file
    std::cout << "Parameters of the dump file:\n";
    std::cout << "d = " << d << "\n";
    std::cout << "n_f = " << n_f << "\n";
    std::cout << "n_p = " << n_p << "\n";

    for(int f=0; f<n_f; f++)
    {
    	// Reads next frame information
    	std::cout << "frame = " << f << "\n" << std::flush;
    	dumpfile.LoadNextFrame(read_file);
        dumpfile.SortByID();
    	dumpfile.Gett(t);
        dumpfile.GetBB(bb_t);
        dumpfile.GetPos(pos_t);

        ncfile.Sett(f,t);
        ncfile.SetPos(f,pos_t);
        ncfile.SetBB(f,bb_t);

    }


    read_file.close();
    ncfile.CloseO();
    std::cout << "\n\n DONE \n\n";

    return 0;

}
