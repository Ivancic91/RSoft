#include "DynamicMeasures.hpp"
#include <vector>

void DynamicMeasures::J2planeAllParticles(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  double theta,
  double phi,
  std::vector<double>& j2_t)
{

  int n_p = pos_t.size();
  j2_t.clear();
  double j2_p;

  for(int p=0; p<n_p; p++)
  {
    J2plane(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, theta, phi, p, j2_p);
    j2_t.push_back(j2_p);
  }

}
