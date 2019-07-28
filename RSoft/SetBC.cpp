#include "RSoft.hpp"

// Sets boundary condition array inside SoftSF instance
// Parameters:
//   bc_t: 1D (dimensions) array of boundary conditions ar time t
// Outputs:
//   None
void RSoft::SetBC(std::vector<std::string>& bc_t)
{

  int num_dim = bc_t.size();
  CheckDim(num_dim);

  bc = bc_t;
  setBC = true;
  calculateRadialSFs = false;
  calculateAngularSFs = false;
}
