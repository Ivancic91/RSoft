#include "DataIO.hpp"
#include <iostream>

void DataIO::SetDefaults()
{

  // Sets default dimension sizes
  if(n_type==-1)
  {
    n_type = 1;
  }
  if(n_bond==-1)
  {
    n_bond = 0;
  }
  if(n_bond_type==-1 and setBond)
  {
    n_bond_type = 1;
  }
  else if(n_bond_type==-1)
  {
    n_bond_type = 0;
  }

  // Sets default arrays
  for(int pp=0; pp<n_p; pp++)
  {
    // initializes default id vector
    if(not setID)
    {
      id.push_back(pp);
    }

    // initializes default type vector
    if(not setType)
    {
      type.push_back(1);
    }

    // initializes default molecule vector
    if(not setMolecule)
    {
      molecule.push_back(0);
    }
  }
  for(int tt=0; tt<n_type; tt++)
  {
    // initializes default mass array
    if(not setMass)
    {
      mass.push_back(1);
    }
  }
  for(int bt=0; bt<n_bond; bt++)
  {
    // initializes default bond type
    if(not setBondType)
    {
      bond_type.push_back(1);
    }
  }

  // Orders outputs by 
  std::vector<int> id_sorted(n_p);
  std::vector<int> molecule_sorted(n_p);
  std::vector<int> type_sorted(n_p);
  std::vector< std::vector<double> > pos_sorted(n_p, std::vector<double>(d));
  std::vector< std::vector<double> > vel_sorted(n_p, std::vector<double>(d));
  for(int p=0; p<n_p; p++)
  {
    id_sorted[id[p]-1] = id[p];
    molecule_sorted[id[p]-1] = molecule[p];
    type_sorted[id[p]-1] = type[p];
    pos_sorted[id[p]-1] = pos[p];
    if(setVel)
    {
      vel_sorted[id[p]-1] = vel[p];
    }
  }
  id = id_sorted;
  molecule = molecule_sorted;
  type = type_sorted;
  pos = pos_sorted;
  vel = vel_sorted;
  
}
