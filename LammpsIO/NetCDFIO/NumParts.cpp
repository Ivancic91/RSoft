#include "NetCDFIO.hpp"

int NetCDFIO::NumParts()
{

  char const* part_dim_label = "atom";
  int n_p_id;
  unsigned long int n_p_temp;

  status = nc_inq_dimid(nc_id, part_dim_label, &n_p_id);
  if (status != NC_NOERR)
    ReportErr(status);
  status = nc_inq_dimlen(nc_id, n_p_id, &n_p_temp);
  if (status != NC_NOERR)
    ReportErr(status);

  n_p = (int)n_p_temp;

  return n_p;

}
