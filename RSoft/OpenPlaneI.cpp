#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <string.h>

// Imports RSoftPlane
// Parameters:
//   nc_file: std::string containing netcdf file name to grab input
// Outputs:
//   None
/**********************************************************************
 * Opens RSoftPlane file for input
 *
 * Opens RSoftPlane file for input. Typically used if one wants to
 * calculcate softness of some dataset.
 *
 * @param[in] nc_file RSoftPlane (netcdf) file to input
 ********************************************************************/
void RSoft::OpenPlaneI(std::string nc_file)
{
 
  // Error warnings 
  if(openPlaneI)
  {
    std::cout << "ERROR: Cannot use OpenPlaneI twice\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(openSFI)
  {
    std::cout << "ERROR: Cannot use OpenSFI and OpenPlaneI together\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Initializes variables for file opening
  char conv_str[12], tmp_str[12];
  double plane_coef, plane_inter;
  unsigned long int n_type_unsigned;
  static size_t idx_type[1];
  static size_t idx_rad_plane[2], idx_ang_plane[2];
  n_SF_rad = 0;  // These two lines are added here because these are 
  n_SF_ang = 0;  // not initialized properly in RSoft for some reason

  // Creates the file. Overwrites previous netCDF file.
  status = nc_open(nc_file.c_str(), NC_NOWRITE, &nc_id_I);
  CheckNCError(status);

  // Checks conventions are correct
  status = nc_get_att_text(nc_id_I, NC_GLOBAL, "Conventions", tmp_str);
  strncpy(conv_str, tmp_str, 10);
  conv_str[10] = 0; // null terminate destination
  if(strcmp(conv_str,"RSoftPlane") != 0 or status != NC_NOERR)
  {
    std::cout << "conv_str = " << conv_str << "\n";
    std::cout << "ERROR: OpenPlaneI can only load RSoftPlane files\n";
    std::cout << std::flush;
    CheckNCError(status);
    std::exit(-1);
  }

  // Gets structure function parameters from nc_id_I
  GetSFParams();

  // Gets type_dim_id and n_type
  status = nc_inq_dimid(nc_id_I, "type", &type_dim_id_I);
  CheckNCError(status);
  status = nc_inq_dimlen(nc_id_I, type_dim_id_I, &n_type_unsigned);
  CheckNCError(status);
  n_type = (int) n_type_unsigned;

  // Loads radial plane for all particle types
  if(containsRadial)
  {
    // Preliminary information about plane
    status = nc_inq_varid(nc_id_I, "radial_plane",
          &radial_plane_var_id_I);
    CheckNCError(status);
    radial_plane.resize(n_type);

    // updates plane vectors
    for(int t=0; t<n_type; t++)
    {
      idx_rad_plane[0] = t;
      for(int SF=0; SF<n_SF_rad; SF++)
      {
        idx_rad_plane[1] = SF;
        status = nc_get_var1_double(nc_id_I, radial_plane_var_id_I,
              idx_rad_plane, &plane_coef);
        CheckNCError(status);
        radial_plane[t].push_back(plane_coef);
      }
    }
  }

  // Loads angular plane for all particle types
  if(containsAngular)
  {
    // Preliminary information about plane
    status = nc_inq_varid(nc_id_I, "angular_plane",
          &angular_plane_var_id_I);
    CheckNCError(status);
    angular_plane.resize(n_type);

    // updates plane vector
    for(int t=0; t<n_type; t++)
    {
      idx_ang_plane[0] = t;
      for(int SF=0; SF<n_SF_ang; SF++)
      {
        idx_ang_plane[1] = SF;
        status = nc_get_var1_double(nc_id_I, angular_plane_var_id_I,
              idx_ang_plane, &plane_coef);
        CheckNCError(status);
        angular_plane[t].push_back(plane_coef);
      }
    }
  }

  // Loads intercept for all particle types
  status = nc_inq_varid(nc_id_I, "intercept", &intercept_var_id_I);
  CheckNCError(status);
  for(int t=0; t<n_type; t++)
  {
    idx_type[0] = t;
    status = nc_get_var1_double(nc_id_I, intercept_var_id_I, idx_type,
          &plane_inter);
    CheckNCError(status);
    intercept.push_back(plane_inter);
  }

  // Marks program as run
  openPlaneI = true;
  
}
