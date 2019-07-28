#include <fstream>
#include <iostream>
#include <cassert>
#include "DumpIO.hpp"

int DumpIO::NumFrames(std::ifstream& read_dump)
{

  if(!run_input or run_output)
  {
    std::cout << "ERROR: running input function after opening output";
    assert(run_input or !run_output);
  }

  n_f = 0;
  current_f = -1;
  std::string line;

  // Rewinds to beginning of file
  assert(read_dump.is_open());
  if(read_dump.eof())
  {
    std::cout << "ERROR: End of File";
    assert(!read_dump.eof());
  }
  read_dump.clear();
  read_dump.seekg(std::ios::beg);

  // Counts number of 'ITEM: ATOMS' are printed in the file
  while(std::getline(read_dump, line))
  {
    if(line.find("ITEM: ATOMS")!=std::string::npos)
    {
      n_f++;
    }
  }

  // Rewinds to beginning of file
  read_dump.clear();
  read_dump.seekg(std::ios::beg);

  return n_f;
}
