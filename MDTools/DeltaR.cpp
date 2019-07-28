#include "MDTools.hpp"
#include "../VectorTools/VectorTools.hpp"

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

