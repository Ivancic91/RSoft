#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Sets box boundaries array inside SoftSF instance
// Parameters:
//   bb_t: 2D (dimensions x 2) array of left and 
//     right boundaries of box at time t. 
// Outputs:
//   None
void RSoft::SetBB(std::vector< std::vector<double> >& bb_t)
{

  int num_dims = bb_t.size();
  CheckDim(num_dims);
  if(bb_t[0].size() != 2)
  {
    std::cout << "\nERROR: Box boundaries array must be ";
    std::cout << "(dimensions x 2) with lower and upper bounds for";
    std::cout << " each dimension.\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  bb = bb_t;
  setBB = true;
  calculateRadialSFs = false;
  calculateAngularSFs = false;
}
