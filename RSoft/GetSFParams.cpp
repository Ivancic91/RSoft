#include "RSoft.hpp"
#include <iostream>
#include <string.h>
#include <algorithm>

// Gets structure function parameters from nc_id_I
// Parameters:
//   None
// Outputs:
//   None
void RSoft::GetSFParams()
{

  char dim_name[NC_MAX_NAME+1];
  double mu, L, xi;
  int radial_X, radial_Y;
  int lambda, zeta, angular_X, angular_Y, angular_Z;
  unsigned long int n_SF_rad_unsigned, n_SF_ang_unsigned;
  unsigned long int dim_length;
  static size_t idx_rad[1], idx_ang[1];
  int n_dim, n_var, n_att, id_unlimited;
  std::vector<int> tmp;


  // Gets number of dimensions, variables, and attributes
  status = nc_inq(nc_id_I, &n_dim, &n_var, &n_att, &id_unlimited);
  CheckNCError(status);

  for(int dim=0; dim<n_dim; dim++)
  {
    // Gets dimension name and length of dimension in question
    status = nc_inq_dim(nc_id_I, dim, dim_name, &dim_length);
    CheckNCError(status);

    // Checks if dimension is radial_structure_functions
    if(strcmp(dim_name,"radial_structure_functions") == 0)
    {
      // Preliminary information about dimension
      containsRadial = true;
      radial_structure_function_dim_id_I = dim;
      n_SF_rad_unsigned = dim_length;
      n_SF_rad = (int) n_SF_rad_unsigned;
      status = nc_get_att_double(nc_id_I, NC_GLOBAL, 
            "radial_error_tolerance", &etol_radial);
      CheckNCError(status);

      // Gets radial structure function variable ids
      status = nc_inq_varid(nc_id_I, "mus", &mus_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "Ls", &Ls_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "radial_Xs", &radial_Xs_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "radial_Ys", &radial_Ys_var_id_I);
      CheckNCError(status);

      // Gets radial structure function variables
      for(int SF=0; SF<n_SF_rad; SF++)
      {
        // Gets values from netCDF file
        idx_rad[0] = SF;
        status = nc_get_var1_double(nc_id_I, mus_var_id_I, idx_rad, &mu);
        CheckNCError(status);
        status = nc_get_var1_double(nc_id_I, Ls_var_id_I, idx_rad, &L);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, radial_Xs_var_id_I, idx_rad,
              &radial_X);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, radial_Ys_var_id_I, idx_rad,
              &radial_Y);
        CheckNCError(status);

        // Loads values into corresponding vectors
        mus.push_back(mu);
        Ls.push_back(L);
        radial_Xs.push_back(radial_X);
        radial_Ys.push_back(radial_Y);
      }
    }

    // Checks if dimension is angular_structure_functions
    if(strcmp(dim_name,"angular_structure_functions") == 0)
    {
      // Preliminary information about dimension
      containsAngular = true;
      angular_structure_function_dim_id_I = dim;
      n_SF_ang_unsigned = dim_length;
      n_SF_ang = (int) n_SF_ang_unsigned;
      status = nc_get_att_double(nc_id_I, NC_GLOBAL,
            "angular_error_tolerance", &etol_angular);
      CheckNCError(status);

      // Gets angular structure function variable ids
      status = nc_inq_varid(nc_id_I, "xis", &xis_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "zetas", &zetas_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "lambdas", &lambdas_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "angular_Xs", &angular_Xs_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "angular_Ys", &angular_Ys_var_id_I);
      CheckNCError(status);
      status = nc_inq_varid(nc_id_I, "angular_Zs", &angular_Zs_var_id_I);
      CheckNCError(status);

      for(int SF=0; SF<n_SF_ang; SF++)
      {
        // Gets values from netCDF file
        idx_ang[0] = SF;
        status = nc_get_var1_double(nc_id_I, xis_var_id_I, idx_ang, &xi);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, zetas_var_id_I, idx_ang, &zeta);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, lambdas_var_id_I, idx_ang,
              &lambda);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, angular_Xs_var_id_I, idx_ang,
              &angular_X);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, angular_Ys_var_id_I, idx_ang,
              &angular_Y);
        CheckNCError(status);
        status = nc_get_var1_int(nc_id_I, angular_Zs_var_id_I, idx_ang,
              &angular_Z);
        CheckNCError(status);

        // Loads values into corresponding vectors
        xis.push_back(xi);
        zetas.push_back(zeta);
        lambdas.push_back(lambda);
        angular_Xs.push_back(angular_X);
        angular_Ys.push_back(angular_Y);
        angular_Zs.push_back(angular_Z);
      }

      // Creates vectors containing all unique elements 
      tmp = angular_Xs;
      std::sort(tmp.begin(), tmp.end());
      tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());   
      unique_angular_Xs = tmp;
      tmp = angular_Ys;
      std::sort(tmp.begin(), tmp.end());
      tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());   
      unique_angular_Ys = tmp;
      tmp = angular_Zs;
      std::sort(tmp.begin(), tmp.end());
      tmp.erase(std::unique(tmp.begin(), tmp.end()), tmp.end());   
      unique_angular_Zs = tmp;
    }

  }
}
