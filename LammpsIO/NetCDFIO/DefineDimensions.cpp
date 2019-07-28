#include "NetCDFIO.hpp"

void NetCDFIO::DefineDimensions()
{
	// Defines dimension label c strings
    char const* frame_dim_label = "frame";
    char const* spatial_dim_label = "spatial";
    char const* cell_spatial_dim_label = "cell_spatial";
    char const* cell_angular_dim_label = "cell_angular";
    char const* label_dim_label = "label";

    // Allows for definition of global attributes/dimensions/variables
    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Defines each dimension for AMBER format except the atom
    // dimension defined in SetPosAndDataDimsAndAtt.cpp
	status = nc_def_dim(nc_id, frame_dim_label, 0, &frame_dim_id);
    if (status != NC_NOERR)
	    ReportErr(status);
    status = nc_def_dim(nc_id, spatial_dim_label, 3, &spatial_dim_id);
    if (status != NC_NOERR)
	    ReportErr(status);
    status = nc_def_dim(nc_id, cell_spatial_dim_label, 3, &cell_spatial_dim_id);
    if (status != NC_NOERR)
 	    ReportErr(status);
    status = nc_def_dim(nc_id, cell_angular_dim_label, 3, &cell_angular_dim_id);
    if (status != NC_NOERR)
	    ReportErr(status);
    status = nc_def_dim(nc_id, label_dim_label, 6, &label_dim_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    // Ends definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
