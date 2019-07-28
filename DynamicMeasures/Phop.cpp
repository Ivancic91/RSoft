#include "DynamicMeasures.hpp"
#include "../MDTools/MDTools.hpp"
#include <vector>
#include <iostream>
#include <math.h>


void DynamicMeasures::Phop(
  std::vector< std::vector< std::vector<double> > >& pos,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  int& t,
  int& t_R, 
  int& m,
  double& phop)
{

  if(t < t_R/2 or t >= pos.size() - t_R/2)
  {
    std::cout << "t = " << t << "\n";
    std::cout << "tR = " << t_R << "\n";
    std::cout << "pos.size() = " << pos.size() << "\n";
    std::cout << "ERROR: t < t_R or t >= T-t_R -- p_hop cannot be computed";
    std::cout << "\n" << std::flush;
  }

  // Declares variables
  int d;
  double val, mu_diff2_A, mu_diff2_B;
  MDTools tool;

  // Initializes variables
  d = pos[0][0].size();
  val = 0.0;
  mu_diff2_A = 0;
  mu_diff2_B = 0;
  std::vector< std::vector<double> > pos_m;
  std::vector<double> mu_rA(d, 0.0);
  std::vector<double> mu_rB(d, 0.0);
  std::vector<double> diff(d, 0.0);

  // Positions of particle m as a function of time. Origin at
  // particle at time t to remove PBC effects
  for(int tt = t-t_R/2; tt <= t+t_R/2; tt++)
  {
    tool.DeltaR(pos[tt][m], pos[t][m], bb_t, bc, diff);
    pos_m.push_back(diff);
  }

  // Average over A/B to obtain mu_rA, mu_rB. Origin at particle
  // at time t to remove PBC effects
  for(int dt=1; dt <= t_R/2; dt++)
  {
    for(int dd=0; dd<d; dd++)
    {
      mu_rA[dd] += pos_m[t-dt][dd];
      mu_rB[dd] += pos_m[t+dt][dd];
    }
  }
  for(int dd=0; dd<d; dd++)
  {
    mu_rA[dd] /= ((double) (t_R/2));
    mu_rB[dd] /= ((double) (t_R/2));
  }

  // Average over A/B to obtain average squared values
  for(int dt=1; dt <= t_R/2; dt++)
  { 
    for(int dd=0; dd<d; dd++)
    {
      val = pos_m[t-dt][dd]-mu_rB[dd];
      mu_diff2_A += val*val;
      val = pos_m[t+dt][dd]-mu_rA[dd];
      mu_diff2_B += val*val;
    }
  }
  mu_diff2_A /= ((double) (t_R/2));
  mu_diff2_B /= ((double) (t_R/2));

  // Calculates p-hop
  phop = sqrt(mu_diff2_A*mu_diff2_B);

}
