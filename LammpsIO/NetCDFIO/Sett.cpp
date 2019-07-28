#include "NetCDFIO.hpp"

void NetCDFIO::Sett(int f, int t)
{
	const unsigned long int ff = (const unsigned long)f;

	// Define the variable. The type of the variable in this case is
	// NC_INT (4-byte integer).
	status = nc_put_var1_int(nc_id, time_var_id, &ff, &t);
	if (status != NC_NOERR)
		ReportErr(status);

}

