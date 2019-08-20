/*
 * MDTools.hpp
 *
 *  Created on: Oct 13, 2016
 *      Author: Robert
 */

#ifndef MDTOOLS_HPP_
#define MDTOOLS_HPP_


#include <vector>
#include "../Eigen/Dense"

/**********************************************************************
 * Molecular dynamics tools for C++
 *
 * MDTools is a class designed to provide some standard molecular 
 * dynamics tools to analyze experimental or simulated trajectories.
 *
 *********************************************************************/
class MDTools
{
private:

  // Variables
  int d;                            // dimension of the space 
  int n_p;                          // # of particles
  std::vector<int> n_cells;         // # of cells in x, y, z
  std::vector<double> cell_lengths; // cell lengths in x, y, z

  // Functions
  void InitializeCellDeltaArr(
        std::vector< std::vector<int> >& delta_cell_arr);
  void BinParticlesIntoCells(
        std::vector< std::vector<double> >& pos_t,
        std::vector< std::vector<double> >& bb_t,
        double R_c,
        std::vector< std::vector<int> >& particles_cell);
  void AddNeighbors(
        std::vector< std::vector<double> >& pos_t,
        std::vector< std::vector<int> >& particles_cell,
        double R_c,
        std::vector<double> shift,
        int cell_idx,
        int neigh_cell_idx,
        std::vector< std::vector<int> >& n_list_t);
  void Stack(
        std::vector<double>& pos, 
        std::vector< std::vector<double> >& bb_t, 
        int& cell_idx);
  void Stack(std::vector<int>& cell_pos, int& cell_idx);
  void Unstack(int& cell_idx, std::vector<int>& cell_pos);
  bool AddCellPos(
        std::vector<int>& cell_pos,
        std::vector<int>& cell_delta,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc,
        std::vector<int>& neighboring_cell_pos,
        std::vector<double>& shift);

public:

  // Publically available MDTools methods
  void PostProcess(
        std::vector< std::vector<double> >& pos_t,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc);
  void GetNList(
        std::vector< std::vector<double> >& pos_t,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc,
        double R_c,
        std::vector< std::vector<int> >& n_list_t);
  void DeltaR(
        std::vector<double>& Rn,
        std::vector<double>& Rm,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc,
        std::vector<double>& RnMinusRm);
  void DeltaR(
        std::vector< std::vector<double> >& Rn,
        std::vector<double>& Rm,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc,
        std::vector< std::vector<double> >& RnMinusRm);
  void DeltaR(
        std::vector< std::vector<double> >& Rn,
        std::vector< std::vector<double> >& Rm,
        std::vector< std::vector<double> >& bb_t,
        std::vector<std::string>& bc,
        std::vector< std::vector<double> >& RnMinusRm);

};


#endif /* MDTOOLS_HPP_ */
