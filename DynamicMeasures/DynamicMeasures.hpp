/*
 * MDTools.hpp
 *
 *  Created on: Nov 1, 2017
 *      Author: Robert
 */

#ifndef DYNAMICMEASURES_HPP_
#define DYNAMICMEASURES_HPP_


#include <vector>
#include "../Eigen/Dense"

class DynamicMeasures
{
private:

  // Variables

  // Functions
  void LambdaMin(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector< std::vector<int> >& n_list_t,
    int m,
    Eigen::MatrixXd& lambda_min_t);


public:

  void KAllParticles(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector<double>& K_t);

  void D2min(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector< std::vector<int> >& n_list_t,
    int& m,
    double& d2min);
  void D2minAllParticles(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector< std::vector<int> >& n_list_t,
    std::vector<double>& d2min);
  void J2(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector< std::vector<int> >& n_list_t,
    int& m,
    double& j2);
  void J2AllParticles(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc,
    std::vector< std::vector<int> >& n_list_t,
    std::vector<double>& j2);
  void J2plane( 
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc, 
    std::vector< std::vector<int> >& n_list_t,
    double theta,
    double phi,
    int& m,
    double& j2);
  void J2planeAllParticles(
    std::vector< std::vector<double> >& pos_t,
    std::vector< std::vector<double> >& bb_t,
    std::vector< std::vector<double> >& pos_dt,
    std::vector< std::vector<double> >& bb_dt,
    std::vector<std::string>& bc, 
    std::vector< std::vector<int> >& n_list_t,
    double theta,
    double phi,
    std::vector<double>& j2);
  void Phop(
    std::vector< std::vector< std::vector<double> > >& pos,
    std::vector< std::vector<double> >& bb_t,
    std::vector<std::string>& bc,
    int& t,
    int& t_R,
    int& m,
    double& phop);
  void PhopAllParticles(
    std::vector< std::vector< std::vector<double> > >& pos,
    std::vector< std::vector<double> >& bb_t,
    std::vector<std::string>& bc,
    int& t,
    int& t_R,
    std::vector<double>& phop);


}; 
#endif /* MDTOOLS_HPP_ */
