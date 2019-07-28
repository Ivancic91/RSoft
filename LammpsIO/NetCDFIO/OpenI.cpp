#include "NetCDFIO.hpp"

void NetCDFIO::OpenI(std::string nc_file_name)
{
  char const* nc_file_name_c = nc_file_name.c_str();

  // Open the file. The NC_NOWRITE parameter tells netCDF to
  // give read only access to this file.
  status = nc_open(nc_file_name_c, NC_NOWRITE, &nc_id);
  if (status != NC_NOERR)
    ReportErr(status);

}
