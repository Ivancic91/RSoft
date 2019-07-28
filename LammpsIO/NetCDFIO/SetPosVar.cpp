#include "NetCDFIO.hpp"

void NetCDFIO::SetPosVar()
{
  // atom (n_p) dimension
  char const* coordinates_dim_label = "coordinates";

  // Allows for definition of global attributes/dimensions/variables
  status = nc_redef(nc_id);
  if (status != NC_NOERR)
    ReportErr(status);

  // Sets up the variable dimensions for coordinates.
  coordinates_var_dims[0] = frame_dim_id;
  coordinates_var_dims[1] = atom_dim_id;
  coordinates_var_dims[2] = spatial_dim_id;

  // Defines coordinate variable
  status = nc_def_var(nc_id, coordinates_dim_label, NC_FLOAT, 3,
        coordinates_var_dims, &coordinates_var_id);
  if (status != NC_NOERR)
    ReportErr(status);

  // Ends definition
  status = nc_enddef(nc_id);
  if (status != NC_NOERR)
    ReportErr(status);

}
