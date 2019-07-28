#include "DataIO.hpp"
#include <set>

void DataIO::SetMolecule(std::vector<int>& molecule_)
{

  int n_p_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setMolecule = true; 
  StatementOrderError();

  // Sets particle types
  molecule = molecule_;
  n_p_local = molecule.size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_p", n_p_local);

}
