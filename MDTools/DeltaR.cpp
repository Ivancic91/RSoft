#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"

/**********************************************************************
 * Difference between two position vectors
 *
 * Calculates the difference between two d-dimensional position vectors
 * Rn and Rm (Rn-Rm) with respect to the box boundaries (bb_t) and the 
 * boundary conditions (bc).
 *
 * @param[in] Rn, Rm the vector to take difference of
 * @param[in] bb_t the box boundaries of simulation or the experiment. 
 *       For d=2, this should be formatted [[low_x, high_x],[low_y, 
 *       high_y]]. In d=3, [[low_x, high_x],[low_y, high_y],[low_z, 
 *       high_z]].
 * @param[in] bc the boundary conditions of the experiment or 
 *       simulation. Each value must be a single character string 
 *       denoting the boundary condition in each direction. ‘p’ means 
 *       periodic boundary conditions. ‘s’ means shrink wrapped 
 *       bounday conditions. ‘f’ means fixed boundary conditions.
 * @param[out] RnMinusRm difference between Rn and Rm with respect to
 *       bb_t and bc.
 *
 *********************************************************************/
void MDTools::DeltaR(
  std::vector<double>& Rn,
  std::vector<double>& Rm,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  std::vector<double>& RnMinusRm)
{
  double dR, L;
  RnMinusRm.clear();
  d = Rn.size();
  assert(Rm.size()==d);

  for(int dd=0; dd<d; dd++)
  {
    dR = Rn[dd] - Rm[dd];
    if(bc[dd]=="p")
    {
      L = bb_t[dd][1] - bb_t[dd][0];
      if(dR > L/2.)
      {
        dR -= L;
      }
      if(dR < -L/2.)
      {
        dR += L;
      }
    }
    RnMinusRm.push_back(dR);
  }
}

/**********************************************************************
 * Difference between set of vectors and a single vector
 *
 * Calculates the difference between a set of d-dimensional position 
 * vectors Rn and a single d-dimensional position vector Rm (Rn-Rm) 
 * with respect to the box boundaries (bb_t) and the boundary 
 * conditions (bc).
 *
 * @param[in] Rn a set of vectors (n_particles, d) of positions to
 *       take difference.
 * @param[in] Rm a single vector to take difference
 * @param[in] bb_t the box boundaries of simulation or the experiment. 
 *       For d=2, this should be formatted [[low_x, high_x],[low_y, 
 *       high_y]]. In d=3, [[low_x, high_x],[low_y, high_y],[low_z, 
 *       high_z]].
 * @param[in] bc the boundary conditions of the experiment or 
 *       simulation. Each value must be a single character string 
 *       denoting the boundary condition in each direction. ‘p’ means 
 *       periodic boundary conditions. ‘s’ means shrink wrapped 
 *       bounday conditions. ‘f’ means fixed boundary conditions.
 * @param[out] RnMinusRm vector of vectors (n_particles, d) which is 
 *       the difference between all vectors in Rn with Rm with respect 
 *       to bb_t and bc.
 *
 *********************************************************************/
void MDTools::DeltaR(
  std::vector< std::vector<double> >& Rn,
  std::vector<double>& Rm,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  std::vector< std::vector<double> >& RnMinusRm)
{
  n_p = Rn.size();
  std::vector<double> x, dx;
  VectorTools vtool;
  vtool.Clear2DVec(RnMinusRm);

  for(int p=0; p<n_p; p++)
  {
    x.clear();
    x = Rn[p];
    DeltaR(x, Rm, bb_t, bc, dx);
    RnMinusRm.push_back(dx);
  }
}

/**********************************************************************
 * Difference between set of vectors and a single vector
 *
 * Calculates the difference between two sets of d-dimensional position 
 * vectors Rn and Rm (Rn-Rm) with respect to the box boundaries (bb_t) 
 * and the boundary conditions (bc).
 *
 * @param[in] Rn, Rm a set of vectors (n_particles, d) of positions to
 *       take difference.
 * @param[in] bb_t the box boundaries of simulation or the experiment. 
 *       For d=2, this should be formatted [[low_x, high_x],[low_y, 
 *       high_y]]. In d=3, [[low_x, high_x],[low_y, high_y],[low_z, 
 *       high_z]].
 * @param[in] bc the boundary conditions of the experiment or 
 *       simulation. Each value must be a single character string 
 *       denoting the boundary condition in each direction. ‘p’ means 
 *       periodic boundary conditions. ‘s’ means shrink wrapped 
 *       bounday conditions. ‘f’ means fixed boundary conditions.
 * @param[out] RnMinusRm set of vectors (n_particles, d) which is 
 *       the difference between all vectors in Rn with all vectors in
 *       Rm with respect to bb_t and bc.
 *
 *********************************************************************/
void MDTools::DeltaR(
  std::vector< std::vector<double> >& Rn,
  std::vector< std::vector<double> >& Rm,
  std::vector< std::vector<double> >& bb_t,
  std::vector<std::string>& bc,
  std::vector< std::vector<double> >& RnMinusRm)
{
  n_p = Rn.size();
  assert(Rm.size()==n_p);
  std::vector<double> xn, xm, dx;
  VectorTools vtool;
  vtool.Clear2DVec(RnMinusRm);

  for(int p=0; p<n_p; p++)
  {
    xn.clear();
    xm.clear();
    xn = Rn[p];
    xm = Rm[p];
    DeltaR(xn, xm, bb_t, bc, dx);
    RnMinusRm.push_back(dx);
  }
}

