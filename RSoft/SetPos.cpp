#include "RSoft.hpp"

// Sets position array inside RSoft object
// Parameters:
//   pos_t: 2D array (n_particles x dimensions) array of particle
//     positions at time t
// Outputs:
//   None
void RSoft::SetPos(std::vector< std::vector<double> >& pos_t)
{

  int num_parts = pos_t.size();
  int num_dims = pos_t[0].size();
  CheckDim(num_dims);
  CheckNumParts(num_parts);

  pos = pos_t;
  setPos = true;
  calculateRadialSFs = false;
  calculateAngularSFs = false;
}
