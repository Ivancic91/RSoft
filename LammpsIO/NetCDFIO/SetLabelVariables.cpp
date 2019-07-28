#include "NetCDFIO.hpp"

void NetCDFIO::SetLabelVariables()
{
	static char char_spatial_arr[] = "xyz";
	static char char_cell_spatial_arr[] = "abc";
	static const char* char_cell_anglular_arr[] = { "alpha", "beta ", "gamma" };



	status = nc_put_var(nc_id, char_spatial_var_id, char_spatial_arr);
	if (status != NC_NOERR)
		ReportErr(status);
	status = nc_put_var(nc_id, char_cell_spatial_var_id, char_cell_spatial_arr);
	if (status != NC_NOERR)
		ReportErr(status);
	status = nc_put_var(nc_id, char_cell_angular_var_id, &char_cell_anglular_arr[0][0]);
	if (status != NC_NOERR)
		ReportErr(status);
}
