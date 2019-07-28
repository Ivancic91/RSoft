#include "DataIO.hpp"

void DataIO::SetMass(std::vector<double>& mass_)
{

  int n_type_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setMass = true; 
  StatementOrderError();

  // Sets particle positions
  mass = mass_;
  n_type_local = mass.size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_type", n_type_local);

}
