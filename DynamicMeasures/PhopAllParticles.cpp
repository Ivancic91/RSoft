#include "DynamicMeasures.hpp"
#include <vector>
#include <iostream>

void DynamicMeasures::PhopAllParticles(
  std::vector< std::vector< std::vector<double> > >& pos,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  int& t,
  int& t_R,
  std::vector<double>& phop)
{

  int n_p = pos[t].size();
  phop.clear();
  double phop_p;

  for(int p=0; p<n_p; p++)
  {
    Phop(pos, bb_t, bc, t, t_R, p, phop_p);
    phop.push_back(phop_p);
  }

}
