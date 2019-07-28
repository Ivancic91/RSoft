#include "DataIO.hpp"
#include <set>

void DataIO::SetBondType(std::vector<int>& bond_type_)
{

  int n_bond_local, n_bond_type_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setBondType = true; 
  StatementOrderError();

  // Sets particle positions
  bond_type = bond_type_;
  n_bond_local = bond_type.size();
  n_bond_type_local = 
          std::set<int>(bond_type.begin(), bond_type.end()).size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_bond", n_bond_local);
  AddDimension("n_bond_type", n_bond_type_local);

}
