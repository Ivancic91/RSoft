#include "NetCDFIO.hpp"


void NetCDFIO::OpenNCO(std::string nc_file_name)
{

    char const* nc_file_name_c = nc_file_name.c_str();

    // Create the file. The NC_CLOBBER parameter tells netCDF to
    // overwrite this file, if it already exists.
    status = nc_create(nc_file_name_c, NC_CLOBBER, &nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Ends definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);


}
