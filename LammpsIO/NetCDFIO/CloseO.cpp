#include "NetCDFIO.hpp"

void NetCDFIO::CloseO()
{
	// Close the file. This frees up any internal netCDF resources
	// associated with the file, and flushes any buffers.
	status = nc_close(nc_id);
	if (status != NC_NOERR)
		ReportErr(status);
}

