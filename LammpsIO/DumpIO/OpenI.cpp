#include <fstream>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

void DumpIO::OpenI(std::ifstream& read_dump)
{
  // opens dump to check if it exists
  //*read_dump = s;
  if ( !read_dump.is_open() )
  {
    std::cout << "\n\nFile did not open.\n\n"<<std::flush;
    assert(read_dump.is_open());
  }
  else
  {
    InitializeParameters();
  }
}
