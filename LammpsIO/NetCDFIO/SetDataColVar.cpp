#include "NetCDFIO.hpp"
#include <string>

void NetCDFIO::SetDataColVar(std::string label, bool is_int)
{

    int dc_var_id;

    // Allows for definition of global attributes/dimensions/variables
    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Sets up the variable dimensions for coordinates.
    dc_var_dims[0] = frame_dim_id;
    dc_var_dims[1] = atom_dim_id;

    // Defines coordinate variable
    if(is_int)
    {
      status = nc_def_var(nc_id, label.c_str(), NC_INT, 2,
            dc_var_dims, &dc_var_id);
    }
    else
    {
      status = nc_def_var(nc_id, label.c_str(), NC_FLOAT, 2,
             dc_var_dims, &dc_var_id);
    }
    if (status != NC_NOERR)
	    ReportErr(status);

    data_col_var_ids.push_back(dc_var_id);

    // Ends definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
