#include "NetCDFIO.hpp"

void NetCDFIO::SetDimAtt()
{
	// atom (n_p) dimension
    char const* dim_att_label = "dimension";

    // Allows for definition of global attributes/dimensions/variables
    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Defines global attribute for dimension of the system
    status = nc_put_att_int(
        nc_id, NC_GLOBAL, dim_att_label, NC_INT, 1, &d);
    if (status != NC_NOERR)
        ReportErr(status);

    // Ends definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
