#include "NetCDFIO.hpp"
#include "../../VectorTools/VectorTools.hpp"

void NetCDFIO::GetPos(int f, std::vector< std::vector<double> >& pos_t)
{

  d = NumDims();
  n_p = NumParts();

  VectorTools vtool;
  char const* coordinate_var_label = "coordinates";
  static size_t idx[3];
  double coordinate;
  std::vector<double> pos_t_dd(d);

  // Clears out previous pos_t values
  vtool.Clear2DVec(pos_t);

  status = nc_inq_varid(nc_id, coordinate_var_label, &coordinates_var_id);
  if (status != NC_NOERR)
    ReportErr(status);

  for(int p=0; p<n_p; p++)
  {
    for (int dd=0; dd<d; dd++)
    {
      idx[0] = f;
      idx[1] = p;
      idx[2] = dd;

      status = nc_get_var1_double(nc_id, coordinates_var_id, idx, &coordinate);
      if (status != NC_NOERR)
        ReportErr(status);

      pos_t_dd[dd] = coordinate;

    }
    pos_t.push_back(pos_t_dd);
  }

}
