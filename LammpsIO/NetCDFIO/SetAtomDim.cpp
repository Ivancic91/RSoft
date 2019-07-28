#include "NetCDFIO.hpp"

void NetCDFIO::SetAtomDim()
{
	// atom (n_p) dimension
    char const* atom_dim_label = "atom";

    // Allows for definition of global attributes/dimensions/variables
    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Defines atom dimension which describes number of particles
    // in simulation
    status = nc_def_dim(nc_id, atom_dim_label, n_p, &atom_dim_id);
    if (status != NC_NOERR)
	    ReportErr(status);

    // Ends definition
    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
