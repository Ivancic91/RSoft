#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"
#include <iostream>

/*

Post-processes Lammps trajectories so that all particles are within the box
for periodic boundary conditions. Particles being slightly outside of periodic
bounds is a common Lammps problem.

pos_t = positions of particles in single frame
bb_t = box boundaries of single frame
bc = boundary conditions of each dimension

*/
void MDTools::PostProcess(
		std::vector< std::vector<double> >& pos_t,
		std::vector< std::vector<double> >& bb_t,
		std::vector<std::string>& bc)
{
  n_p = pos_t.size();
  d = pos_t[0].size();

  VectorTools vtool;
  double epsilon = 0.000000001;

  for(int dd=0; dd<d; dd++)
  {
    if(bc[dd]=="p")
    {
      for(int p=0; p<n_p; p++)
      {
        if(pos_t[p][dd] > bb_t[dd][1])
        {
          pos_t[p][dd] -= (bb_t[dd][1] - bb_t[dd][0]);
        }
        if(pos_t[p][dd] < bb_t[dd][0])
        {
          pos_t[p][dd] += (bb_t[dd][1] - bb_t[dd][0]);
				}
        if(pos_t[p][dd] == bb_t[dd][1])
        {
          pos_t[p][dd] -= epsilon;
        }
        if(pos_t[p][dd] == bb_t[dd][0])
        {
          pos_t[p][dd] += epsilon;
        }
      } 
    }
    else
    {
      bb_t[dd][1] = vtool.MaxCol(pos_t,dd) + epsilon;
      bb_t[dd][0] = vtool.MinCol(pos_t,dd) - epsilon;
    }
  }
}
