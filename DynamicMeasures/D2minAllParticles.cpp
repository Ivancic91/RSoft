#include "DynamicMeasures.hpp"
#include <vector>

void DynamicMeasures::D2minAllParticles(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector< std::vector<int> >& n_list_t,
  std::vector<double>& d2min_t)
{
  int n_p = pos_t.size();
  d2min_t.clear();
  double d2min_p;

  for(int p=0; p<n_p; p++)
  {
    D2min(pos_t, bb_t, pos_dt, bb_dt, bc, n_list_t, p, d2min_p);
    d2min_t.push_back(d2min_p);
  }

}
