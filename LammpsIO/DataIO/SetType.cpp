#include "DataIO.hpp"
#include <set>

void DataIO::SetType(std::vector<int>& type_)
{

  int n_p_local, n_type_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setType = true; 
  StatementOrderError();

  // Sets particle types
  type = type_;
  n_p_local = type.size();
  n_type_local = std::set<int>(type.begin(), type.end()).size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_p", n_p_local);
  AddDimension("n_type", n_type_local);

}
