#include "DataIO.hpp"
#include <iostream>

void DataIO::SetPos(std::vector< std::vector<double> >& pos_)
{

  int n_p_local, d_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setPos = true; 
  StatementOrderError();

  // Sets particle positions
  pos = pos_;
  n_p_local = pos.size();
  d_local = pos[0].size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_p", n_p_local);
  AddDimension("d", d_local); 

}
