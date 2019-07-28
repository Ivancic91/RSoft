#include "DataIO.hpp"
#include <iostream>
#include <sstream>
#include <cassert>

void DataIO::SetBond(std::vector< std::vector<int> >& bond_)
{

  int n_bond_local;

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  setBond = true; 
  StatementOrderError();

  // Sets particle positions
  bond = bond_;
  n_bond_local = bond.size();
  
  // Adds dimensions to ensure array correct size
  AddDimension("n_bond", n_bond_local);
  if(bond[0].size() != 2)
  {
    std::cout << "ERROR: bonds must be n_bonds x 2\n";
    std::cout << std::flush;
    assert(false);
  }

}

void DataIO::SetBond(std::string bond_mode)
{

  // Error SetPos must be used before SetBond
  if(not setPos or not setID)
  {
    std::cout << "ERROR: SetPos and SetID  must be used before\n";
    std::cout << "  setting bonds by bond mode\n";
    std::cout << std::flush;
    assert(false);
  }

  // Initializes variables
  std::vector<std::string> mode_vec;
  std::string tmp;

  // Splits bond_mode string
  std::istringstream iss(bond_mode);
  while(iss >> tmp)
  {
    mode_vec.push_back(tmp);
  }
  
  // creates bond list for various modes:
  // (1) Linear polymer: creates linear polymer bonds with a chain
  //     length of chlen. To use, string should be
  //     "linear_polymer chlen". Particles should be ordered by bond,
  //     i.e. particle 0 connects to particle 1, ect.
  if(mode_vec[0] == "linear_polymer")
  {
    int chlen = atoi(mode_vec[1].c_str());   // chain length
    int mol_id;                              // molecular id
    int id_pp;                               // id of particle
    std::vector< std::vector<int> > bond_;
    std::vector<int> indiv_bond_;
    std::vector<int> molecule_;
    indiv_bond_.resize(2);

    // checks all particles part of chain
    if(n_p % chlen != 0)
    {
      std::cout << "ERROR: Not all monomers are part of chain\n";
      std::cout << std::flush;
      assert(false);
    }

    // creates bond list
    for(int pp=0; pp<n_p; pp++)
    {
      if(pp%chlen != chlen-1)
      {
        indiv_bond_[0] = pp+1;
        indiv_bond_[1] = pp+2;
        bond_.push_back(indiv_bond_);
      }
      id_pp = id[pp];
      mol_id = chlen+1-abs((2*id_pp-1)%(2*chlen)-chlen);
      mol_id = mol_id/2;
      molecule_.push_back(mol_id);
    }

    // Sets bond list
    SetBond(bond_);
    SetMolecule(molecule_);
    
  } else
  {
    std::cout << "ERROR: bond_mode = " << mode_vec[0] << "is not\n";
    std::cout << "  included in the current list of bond modes.\n";
    std::cout << std::flush;
    assert(false);
  }

}


