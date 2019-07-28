#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "DumpIO.hpp"

void DumpIO::WriteDataFile(
  std::string str_output,
  std::vector< std::vector<double> >& bb_t, 
  std::vector<int>& id_t,
  std::vector<double>& type_t,
  std::vector< std::vector<double> >& pos_t)
{

  // Opens file
  std::ofstream write_data;
  write_data.open(str_output.c_str());

  // Writes the header
  write_data << "LAMMPS data file via BASECODE, version 23 Feb 2018\n\n";
  write_data << pos_t.size() << " atoms\n";
  write_data << "2 atom types\n\n";

  // Write box boundaries
  std::vector< std::string > dim_name;
  dim_name.push_back("x");
  dim_name.push_back("y");
  dim_name.push_back("z");
  for(int dd=0; dd<bb_t.size(); dd++)
  {
    write_data << bb_t[dd][0] << " ";
    write_data << bb_t[dd][1] << " ";
    write_data << dim_name[dd] << "lo ";
    write_data << dim_name[dd] << "hi\n";
  }
  write_data << "\n";

  // Writes masses and pair coeffs
  write_data << "Masses\n\n";
  write_data << "1 1\n";
  write_data << "2 1\n\n";
  write_data << "Pair Coeffs # lj/cut\n\n";
  write_data << "1 1 1\n";
  write_data << "2 0.5 0.88\n\n";

  // Writes atomic positions
  write_data << "Atoms # atomic\n\n";
  for(int p=0; p<pos_t.size(); p++)
  {
    write_data <<  id_t[p] << " ";
    write_data << (int) type_t[p] << " ";
    write_data << pos_t[p][0] << " ";
    write_data << pos_t[p][1] << " ";
    write_data << pos_t[p][2] << "\n";
  }
  // write_data << "\n";

  // Writes atomic velocities
  // write_data << "Velocities\n\n";
  // for(int p=0; p<pos_t.size(); p++)
  // {
  //  write_data << id_t[p] << " ";
  //  write_data << vx_t[p] << " ";
  //  write_data << vy_t[p] << " ";
  //  write_data << vz_t[p] << "\n";
  // }

  write_data.close();

}
