#include "DynamicMeasures.hpp"
#include "../MDTools/MDTools.hpp"
#include <vector>
#include <iostream>


void DynamicMeasures::KAllParticles(
  std::vector< std::vector<double> >& pos_t,
  std::vector< std::vector<double> >& bb_t,
  std::vector< std::vector<double> >& pos_dt,
  std::vector< std::vector<double> >& bb_dt,
  std::vector<std::string>& bc,
  std::vector<double>& K_t)
{

  // Declares variables
  int n_p = pos_t.size();                    // num particles
  int d = pos_t[0].size();                   // dimension of space
  double K;                                  // K for particle
  double dx;                                 // diff in pos
  std::vector<std::vector<double>> bb_avg;   // average box bound
  std::vector<double> bb_tmp(2);
  std::vector< std::vector<double> > dR;     // diff vector array

  // Clears K_t to ready for new variables
  K_t.clear();

  // Averages bb_t and bb_dt arrays
  for(int dd=0; dd<d; dd++)
  {
    bb_avg.push_back(bb_tmp);
    bb_avg[dd][0] = 0.5*(bb_t[dd][0]+bb_dt[dd][0]);
    bb_avg[dd][1] = 0.5*(bb_t[dd][1]+bb_dt[dd][1]);
  }

  // Calculates separation vector
  tool.DeltaR(pos_dt, pos_t, bb_avg, bc, dR);

  // For each particle, squares and sums difference to K
  for(int p=0; p<n_p; p++)
  {
    K = 0;
    for(int dd=0; dd<d; dd++)
    {
      dx = dR[p][dd];
      K += dx*dx;
    }
    K_t.push_back(K);
  }

}
