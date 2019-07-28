#include "NetCDFIO.hpp"

void NetCDFIO::Gett(int f, int t)
{

	char const* t_var_label = "time";
	const unsigned long int ff = (const unsigned long int)f;

	status = nc_inq_varid(nc_id, t_var_label, &time_var_id);
    if (status != NC_NOERR)
    	ReportErr(status);
	status = nc_get_var1_int(nc_id, time_var_id, &ff, &t);
    if (status != NC_NOERR)
    	ReportErr(status);

}
