#include "NetCDFIO.hpp"

int NetCDFIO::NumDims()
{

  char const* dim_att_label = "dimension";
  status = nc_get_att_int(nc_id, NC_GLOBAL, dim_att_label, &d);
  if (status == NC_ENOTATT)
  {
    d = 3; // Assume 3D unless dimensions attribute exists
  }
  else
  {
    if (status != NC_NOERR)
    {
      ReportErr(status);
    }
  }
  return d;
}
