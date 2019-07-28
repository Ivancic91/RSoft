#include "DataIO.hpp"

void DataIO::SetID(std::vector<int>& id_)
{

  int n_p_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setID = true; 
  StatementOrderError();

  // Sets particle ids
  id = id_;
  n_p_local = id.size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_p", n_p_local);

}
