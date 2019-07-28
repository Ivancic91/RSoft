#include "RSoft.hpp"

// Sets atom type array inside SoftSF instance
// Parameters:
//   type_t: 1D (n_particles) array of each particle type
// Outputs:
//   None
void RSoft::SetType(std::vector<int>& type_t)
{

  int num_parts = type_t.size();
  CheckNumParts(num_parts);

  type = type_t;
  setType = true;
  calculateRadialSFs = false;
  calculateAngularSFs = false;
}
