#include "RSoft.hpp"
#include "../MDTools/MDTools.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <algorithm>

// Calculates the neighbor and r_ij list for the radial and angular
// structure funcitons
// Parameters:
//   None
// Outputs:
//   None
void RSoft::CalculateNListRList()
{

  // Function does nothing if calculate radial or angular has already 
  // been called and sets have not been changed.
  if(!calculateRadialSFs and !calculateAngularSFs)
  {

    // Initializes several variables
    MDTools tool;
    int n_neigh, pp_neigh;
    double R2;
    double Rc_radial, Rc_angular, Rc;
    std::vector< std::vector<int> > n_list;    // neighbor list
    std::vector<double> dr;                    // delta positions

    // Clears previous lists
    n_list_angular.clear();
    n_list_angular.resize(n_p);
    n_list_radial.clear();
    n_list_radial.resize(n_p);

    // Gets neighbor list, calculates Rc for the radial structure
    // functions, and initializes SFs_radial
    Rc_radial = GetRcRadial();
    Rc_angular = GetRcAngular();
    Rc = std::max(Rc_radial,Rc_angular);
    tool.PostProcess(pos, bb, bc);
    tool.GetNList(pos, bb, bc, Rc, n_list);

    // For each particle, calculates structure functions from all
    // neighbors
    for(int pp=0; pp<n_p; pp++)
    {
      n_neigh = n_list[pp].size();
      for(int nn=0; nn<n_neigh; nn++)
      {
        // Finds distance between particle and neighbor
        R2 = 0.0;
        pp_neigh = n_list[pp][nn];
        tool.DeltaR(pos[pp], pos[pp_neigh], bb, bc, dr);
        for(int dd=0; dd<d; dd++)
          R2 += dr[dd]*dr[dd];

        if(R2<Rc_radial*Rc_radial)
        {
          n_list_radial[pp].push_back(pp_neigh);
        }
        if(R2<Rc_angular*Rc_angular)
        {
          n_list_angular[pp].push_back(pp_neigh);
        }
      }
    }
  }
}
