#include "NetCDFIO.hpp"

void NetCDFIO::DefineVariables()
{

    // Sets up the variable dimensions for all variables
    // in AMBER except coordinates
    char_spatial_var_dims[0] = spatial_dim_id;
    char_cell_spatial_var_dims[0] = cell_spatial_dim_id;
    char_cell_angular_var_dims[0] = cell_angular_dim_id;
    char_cell_angular_var_dims[1] = label_dim_id;
    time_var_dims[0] = frame_dim_id;
    cell_origin_var_dims[0] = frame_dim_id;
    cell_origin_var_dims[1] = cell_spatial_dim_id;
    cell_lengths_var_dims[0] = frame_dim_id;
    cell_lengths_var_dims[1] = cell_spatial_dim_id;
    cell_angles_var_dims[0] = frame_dim_id;
    cell_angles_var_dims[1] = cell_angular_dim_id;


    // Allows for definition of global attributes/dimensions/variables
    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

	// Sets up the standard variables for AMBER format
	status = nc_def_var(nc_id, "char spatial", NC_CHAR, 1,
    		char_spatial_var_dims, &char_spatial_var_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    status = nc_def_var(nc_id, "char cell_spatial", NC_CHAR, 1,
    		char_cell_spatial_var_dims, &char_cell_spatial_var_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    status = nc_def_var(nc_id, "char cell_angular", NC_CHAR, 2,
    		char_cell_angular_var_dims, &char_cell_angular_var_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    status = nc_def_var(nc_id, "time", NC_INT, 1,
    		time_var_dims, &time_var_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    status = nc_def_var(nc_id, "cell_origin", NC_FLOAT, 2,
    		cell_origin_var_dims, &cell_origin_var_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    status = nc_def_var(nc_id, "cell_lengths", NC_FLOAT, 2,
    		cell_lengths_var_dims, &cell_lengths_var_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    status = nc_def_var(nc_id, "cell_angles", NC_FLOAT, 2,
    		cell_angles_var_dims, &cell_angles_var_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    // Closes for definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
