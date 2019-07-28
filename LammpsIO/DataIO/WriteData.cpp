#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "DataIO.hpp"

void DataIO::WriteData(
  std::ofstream& write_data)
{

  // Checks order of functions is correct before and after
  // modifying function tag
  StatementOrderError();
  writeDataFile = true;
  StatementOrderError();

  // Set default parameters
  SetDefaults();

  // Writes the header
  write_data << "LAMMPS data file via BASECODE/LammpsIO/DataIO";
  write_data << ", version 30 July 2018\n\n";

  // Writes first section
  write_data << n_p << " atoms\n";
  write_data << n_bond << " bonds\n";
  write_data << "0 angles\n";
  write_data << "0 dihedrals\n";
  write_data << "0 impropers\n\n";

  // Writes second section
  write_data << n_type << " atom types\n";
  if(n_bond_type != 0)
  {
    write_data << n_bond_type << " bond types\n";
  }
  write_data << "\n";

  // Write box boundaries
  std::vector< std::string > dim_name;
  dim_name.push_back("x");
  dim_name.push_back("y");
  dim_name.push_back("z");
  for(int dd=0; dd<d; dd++)
  {
    write_data << bb[dd][0] << " ";
    write_data << bb[dd][1] << " ";
    write_data << dim_name[dd] << "lo ";
    write_data << dim_name[dd] << "hi\n";
  }
  write_data << "\n";

  // Writes masses and pair coeffs
  write_data << "Masses\n\n";
  for(int tt=0; tt<n_type; tt++)
  {
    write_data << tt+1 << " " << mass[tt] << "\n";
  }
  write_data << "\n";

  // Writes atomic positions
  write_data << "Atoms\n\n";
  for(int p=0; p<n_p; p++)
  {
    write_data << id[p] << " ";
    write_data << molecule[p] << " ";
    write_data << type[p] << " ";
    for(int dd=0; dd<d-1; dd++)
    {
      write_data << pos[p][dd] << " ";
    }
    write_data << pos[p][d-1] << "\n";
  }
  write_data << "\n";

  // Writes atomic velocities
  if(setVel)
  {
    write_data << "Velocities\n\n";
    for(int p=0; p<n_p; p++)
    {
      write_data << id[p] << " ";
      for(int dd=0; dd<d-1; dd++)
      {
        write_data << vel[p][dd] << " ";
      }
      write_data << vel[p][d-1] << "\n";
    }
    write_data << "\n";
  }

  // Writes bonds
  if(setBond)
  {
    write_data << "Bonds\n\n";
    for(int bd=0; bd<n_bond; bd++)
    {
      write_data << bd+1 << " ";
      write_data << bond_type[bd] << " ";
      write_data << bond[bd][0] << " ";
      write_data << bond[bd][1] << "\n";
    }
    write_data << "\n";
  }
}
