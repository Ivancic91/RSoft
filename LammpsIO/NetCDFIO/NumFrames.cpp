#include "NetCDFIO.hpp"

int NetCDFIO::NumFrames()
{


	char const* frame_dim_label = "frame";
	unsigned long int n_f_temp;
	int n_f_id;


	status = nc_inq_dimid(nc_id,frame_dim_label, &n_f_id);
    if (status != NC_NOERR)
    	ReportErr(status);

	status = nc_inq_dimlen(nc_id,n_f_id, &n_f_temp);
    if (status != NC_NOERR)
    	ReportErr(status);

    n_f = (int)n_f_temp;

	return n_f;
}
