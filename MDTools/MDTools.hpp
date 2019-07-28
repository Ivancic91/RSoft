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

class MDTools
{
private:

  // Variables
  int d, n_p;
  std::vector<int> n_cells;
  std::vector<double> cell_lengths;

  // Functions
  void InitializeCellDeltaArr(std::vector< std::vector<int> >& delta_cell_arr);
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
  void Stack(std::vector<double>& pos, std::vector< std::vector<double> >& bb_t, int& cell_idx);
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

  void BinParticlesIntoCellsPub(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    double R_c,
    std::vector< std::vector<int> >& particles_cell);
  void GetCellPos(
    std::vector< std::vector<double> >& bb_t,
    double R_c,
    std::vector< std::vector<double> >& cell_pos_arr,
    double& L_cut_cell);

};


#endif /* MDTOOLS_HPP_ */
