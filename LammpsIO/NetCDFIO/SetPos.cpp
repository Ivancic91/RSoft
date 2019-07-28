#include "NetCDFIO.hpp"

void NetCDFIO::SetPos(int f, std::vector< std::vector<double> >& pos_t)
{

  if(d==-1)
  {
    d = pos_t[0].size();
    SetDimAtt();
  }
  if(n_p==-1)
  {
    n_p = pos_t.size();
    SetAtomDim();
  }
  if(!run_SetPos)
  {
    SetPosVar();
  }

  static size_t idx[3];
  double var;

  // Define the variable. The type of the variable in this case is
  // NC_INT (4-byte integer).
  for (int p=0; p<n_p; p++)
  {
    for (int dd=0; dd<3; dd++)
    {
      idx[0] = f;
      idx[1] = p;
      idx[2] = dd;

      // If data is 2D puts 0's in
      // the z coordinate
      if(dd!=d)
      {
        var = pos_t[p][dd];
      }
      else
      {
        var = 0;
      }

      status = nc_put_var1_double(nc_id, coordinates_var_id, idx, &var);
      if (status != NC_NOERR)
        ReportErr(status);
    }
  }

  run_SetPos = true;

}

