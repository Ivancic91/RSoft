/*
 * LammpsIO.hpp
 *
 *  Created on: Sep 20, 2016
 *      Author: Robert
 */

#ifndef DATAIO_HPP_
#define DATAIO_HPP_

#include <vector>
#include <string>
#include <stdlib.h>

class DataIO
{
private:

  // Shared variables
  //-----------------------------------------------------//
  int d;            // Dimension of space
  int n_p;          // Number of particles
  int n_type;       // Number of particle types
  int n_bond;       // Number of bonds
  int n_bond_type;  // Number of bond types

  // data arrays
  std::vector< std::vector<double> > pos; // particle positions n_p x d
  std::vector< std::vector<double> > bb;  // box bounds d x 2
  std::vector<int> id;                    // particle ids n_p
  std::vector<int> type;                  // particle type n_p
  std::vector<int> molecule;              // particle mol n_p
  std::vector<double> mass;               // particle mass n_type
  std::vector< std::vector<int> > bond;   // bond list n_bond x 2
  std::vector<int> bond_type;             // type of bond n_bond
  std::vector< std::vector<double> > vel; // particle velocity n_p x d

  // Input variables
  //-----------------------------------------------------//

  // Output variables
  //-----------------------------------------------------//
  bool openO;                      // Tag for having run OpenO
  bool setPos;                     // Tag for having run SetPos
  bool setBB;                      // Tag for having run SetBB
  bool setID;                      // Tag for having run SetID
  bool setType;                    // Tag for having run SetType
  bool setMass;                    // Tag for having run SetMass
  bool setMolecule;                // Tag for having run SetMolecule
  bool setBond;                    // Tag for having run SetBond
  bool setBondType;                // Tag for having run SetBondType
  bool setVel;                     // Tag for having run SetVel
  bool writeDataFile;              // Tag for having run SetDataFile

  // Initializes standard error functions
  void StatementOrderError();
  void AddDimension(std::string dim, int dim_size);
  void SetDefaults();

public:

  // Initializes private variables
  DataIO()
  {
    // Initializes dimension sizes
    d = -1;
    n_p = -1;
    n_type = -1;
    n_bond = -1;
    n_bond_type = -1;

    // Initializes function use tags
    openO = false;
    setPos = false;
    setBB = false;
    setID = false;
    setType = false;
    setMass = false;
    setMolecule = false;
    setBond = false;
    setBondType = false;
    setVel = false;
    writeDataFile = false;
  }

  void OpenO(std::ofstream& write_data);
  void SetPos(std::vector< std::vector<double> >& pos_);
  void SetBB(std::vector< std::vector<double> >& bb_);
  void SetID(std::vector<int>& id_);
  void SetType(std::vector<int>& type_);
  void SetMass(std::vector<double>& mass_);
  void SetMolecule(std::vector<int>& molecule_);
  void SetBond(std::string bond_mode_);
  void SetBond(std::vector< std::vector<int> >& bond_);
  void SetBondType(std::vector<int>& bond_type_);
  void SetVel(std::vector< std::vector<double> >& vel_);
  void WriteData(std::ofstream& write_data);


};


#endif /* DATAIO_HPP_ */


