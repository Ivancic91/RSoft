#include <fstream>
#include <iostream>
#include <cassert>
#include "DataIO.hpp"

void DataIO::AddDimension(std::string dim, int dim_size)
{

  // dimension dimension
  if(dim == "d" and d!=-1 and dim_size!=d)
  {
    std::cout << "ERROR: d dimensions do not match\n";
    std::cout << d << " != " << dim_size << "\n";
    std::cout << std::flush;
    assert(false);
  } else if(dim == "d"){
    d = dim_size;
  }

  // number of particles dimension
  if(dim == "n_p" and n_p!=-1 and dim_size!=n_p)
  {
    std::cout << "ERROR: number of particles do not match\n";
    std::cout << n_p << " != " << dim_size << "\n";
    std::cout << std::flush;
    assert(false);
  } else if(dim == "n_p"){
    n_p = dim_size;
  }

  // number of types dimension
  if(dim == "n_type" and n_type!=-1 and dim_size!=n_type)
  {
    std::cout << "ERROR: number of particles do not match\n";
    std::cout << n_type << " != " << dim_size << "\n";
    std::cout << std::flush;
    assert(false);
  } else if(dim == "n_type"){
    n_type = dim_size;
  }

  // number of bonds dimension
  if(dim == "n_bond" and n_bond!=-1 and dim_size!=n_bond)
  {
    std::cout << "ERROR: number of particles do not match\n";
    std::cout << n_bond << " != " << dim_size << "\n";
    std::cout << std::flush;
    assert(false);
  } else if(dim == "n_bond"){
    n_bond = dim_size;
  }

  // number of bond types dimension
  if(dim == "n_bond_type" and n_bond_type!=-1 and dim_size!=n_bond_type)
  {
    std::cout << "ERROR: number of particles do not match\n";
    std::cout << n_bond_type << " != " << dim_size << "\n";
    std::cout << std::flush;
    assert(false);
  } else if(dim == "n_bond_type"){
    n_bond_type = dim_size;
  }

}
