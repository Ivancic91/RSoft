#include <fstream>
#include <iostream>
#include <cassert>
#include "DataIO.hpp"

void DataIO::StatementOrderError()
{
  bool setUsed;

  // Checks if set statement used
  setUsed = setPos or setBB or setID or setType or setMass or setBond;
  setUsed = setUsed or setBondType or setVel or setMolecule;

  // Checks output opened before set statement used
  if(not openO and setUsed)
  {
    std::cout << "ERROR: Cannot use set statement before opening\n";
    std::cout << "  output\n";
    std::cout << std::flush;
    assert(false);
  }

  // Checks output opened before data file written
  if(not openO and writeDataFile)
  {
    std::cout << "ERROR: Cannot write data file before opening\n";
    std::cout << "  output\n";
    std::cout << std::flush;
    assert(false);
  }

  // Checks positions and box boundaries set before writing data
  // file.
  if(not (setPos and setBB) and writeDataFile)
  {
    std::cout << "ERROR: Must set positions and box bounds before\n";
    std::cout << "  writing data file\n";
    std::cout << std::flush;
    assert(false);
  }


}
