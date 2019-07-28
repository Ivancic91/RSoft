#include <iostream>
#include <cassert>
#include "DataIO.hpp"

void DataIO::SetBB(std::vector< std::vector<double> >& bb_)
{

  int d_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setBB = true; 
  StatementOrderError();

  // Sets box bounds
  bb = bb_;
  d_local = bb.size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("d", d_local); 
  if(bb[0].size() != 2)
  {
    std::cout << "ERROR: box boundaries must be d x 2\n";
    std::cout << std::flush;
    assert(false);
  }
}
