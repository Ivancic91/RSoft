#include "DataIO.hpp"

void DataIO::SetVel(std::vector< std::vector<double> >& vel_)
{

  int n_p_local, d_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setVel = true; 
  StatementOrderError();

  // Sets particle positions
  vel = vel_;
  n_p_local = vel.size();
  d_local = vel[0].size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_p", n_p_local);
  AddDimension("d", d_local); 

}
