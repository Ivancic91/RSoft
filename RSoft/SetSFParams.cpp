#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <string.h>

// Sets structure function parameters for RSoftSF or RSoftPlane file
// Parameters:
//   nc_file: std::string containing netcdf file name to output to
// Outputs:
//   None
void RSoft::SetSFParams()
{
 // Initializes variables
  int radial_SF_var_dims[1];
  static double etol_radial_arr[] = {etol_radial};
  int angular_SF_var_dims[1];
  static double etol_angular_arr[] = {etol_angular};
  static size_t idx_rSF[1], idx_aSF[1];

  // Allows for definition of global attributes/dimensions/variables
  status = nc_redef(nc_id_O);
  CheckNCError(status);

  // If radial structure functions are in output
  if(containsRadial)
  {
    // Defines radial attributes
    status = nc_put_att_double(nc_id_O, NC_GLOBAL, 
          "radial_error_tolerance", NC_FLOAT, 1, etol_radial_arr);
    CheckNCError(status);

    // Defines radial dimensions
    status = nc_def_dim(nc_id_O, "radial_structure_functions",
          n_SF_rad, &radial_structure_function_dim_id_O);
    CheckNCError(status);

    // Defines radial variables
    radial_SF_var_dims[0] = radial_structure_function_dim_id_O;
    status = nc_def_var(nc_id_O, "mus", NC_FLOAT, 1, radial_SF_var_dims,
          &mus_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "Ls", NC_FLOAT, 1, radial_SF_var_dims,
          &Ls_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "radial_Xs", NC_INT, 1, radial_SF_var_dims,
          &radial_Xs_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "radial_Ys", NC_INT, 1, radial_SF_var_dims,
          &radial_Ys_var_id_O);
    CheckNCError(status);

    // Temporarily closes for definition to set radial SF variables
    status = nc_enddef(nc_id_O);
    CheckNCError(status);

    // Sets radial structure function variables
    for(int SF=0; SF<n_SF_rad; SF++)
    {
      idx_rSF[0] = SF;
      status = nc_put_var1_double(nc_id_O, mus_var_id_O, idx_rSF, &mus[SF]);
      CheckNCError(status);
      status = nc_put_var1_double(nc_id_O, Ls_var_id_O, idx_rSF, &Ls[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, radial_Xs_var_id_O, idx_rSF,
            &radial_Xs[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, radial_Ys_var_id_O, idx_rSF,
            &radial_Ys[SF]);
      CheckNCError(status);
    }

    // Reopens definition
    status = nc_redef(nc_id_O);
    CheckNCError(status);
  }

  // If angular structure functions are in output
  if(containsAngular)
  {
    // Defines angular attributes
    status = nc_put_att_double(nc_id_O, NC_GLOBAL, 
          "angular_error_tolerance", NC_FLOAT, 1, etol_angular_arr);
    CheckNCError(status);

    // Defines angular dimensions
    status = nc_def_dim(nc_id_O, "angular_structure_functions",
          n_SF_ang, &angular_structure_function_dim_id_O);
    CheckNCError(status);

    // Defines angular variables
    angular_SF_var_dims[0] = angular_structure_function_dim_id_O;
    status = nc_def_var(nc_id_O, "xis", NC_FLOAT, 1,
          angular_SF_var_dims, &xis_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "zetas", NC_FLOAT, 1,
          angular_SF_var_dims, &zetas_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "lambdas", NC_INT, 1,
          angular_SF_var_dims, &lambdas_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "angular_Xs", NC_INT, 1,
          angular_SF_var_dims, &angular_Xs_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "angular_Ys", NC_INT, 1,
          angular_SF_var_dims, &angular_Ys_var_id_O);
    CheckNCError(status);
    status = nc_def_var(nc_id_O, "angular_Zs", NC_INT, 1,
          angular_SF_var_dims, &angular_Zs_var_id_O);
    CheckNCError(status);

    // Temporarily closes for definition to set angular SF variables
    status = nc_enddef(nc_id_O);
    CheckNCError(status);

    // Sets angular structure function variables
    for(int SF=0; SF<n_SF_ang; SF++)
    {
      idx_aSF[0] = SF;
      status = nc_put_var1_double(nc_id_O, xis_var_id_O, idx_aSF,
            &xis[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, zetas_var_id_O, idx_aSF,
            &zetas[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, lambdas_var_id_O, idx_aSF,
            &lambdas[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, angular_Xs_var_id_O, idx_aSF,
            &angular_Xs[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, angular_Ys_var_id_O, idx_aSF,
            &angular_Ys[SF]);
      CheckNCError(status);
      status = nc_put_var1_int(nc_id_O, angular_Zs_var_id_O, idx_aSF,
        &angular_Zs[SF]);
      CheckNCError(status);
    }

    // Reopens definition
    status = nc_redef(nc_id_O);
    CheckNCError(status);
  }

  // Closes for definition
  status = nc_enddef(nc_id_O);
  CheckNCError(status);
}
