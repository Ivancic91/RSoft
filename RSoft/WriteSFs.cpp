#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

// Writes calculated structure functions to frame f in netCDF file
// Parameters:
//   nc_file: std::string containing netcdf file name to output to
//   traj_str: std::string containing name of trajectory used for SF
//     calculations
// Outputs:
//   None
void RSoft::WriteSFs(int f)
{

  // Ensures that correct functions have been run before writing
  // netCDF file
  if(!openSFO)
  {
    std::cout << "ERROR: Must use OpenSFO before WriteSF\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(!openSFI and !openPlaneI)
  {
    std::cout << "ERROR: Must use OpenSFI or OpenPlaneI";
    std::cout << " before WriteSF\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(!calculateRadialSFs && containsRadial)
  {
    CalculateRadialSFs();
  }
  if(!calculateAngularSFs && containsAngular)
  {
    CalculateAngularSFs();
  }


  // Declares variables
  static size_t idx_rad[3], idx_ang[3];
  int radial_structures_var_dims[3];
  int angular_structures_var_dims[3];

  // Defines variables to store structure functions if writeSF has not
  // been used before
  if(not writeSF)
  {
    // Defines frame and atom dimensions
    status = nc_redef(nc_id_O);
    CheckNCError(status);
    status = nc_def_dim(nc_id_O, "frame", 0, &frame_dim_id_O);
    CheckNCError(status);
    status = nc_def_dim(nc_id_O, "atom", n_p, &atom_dim_id_O);
    CheckNCError(status);
    status = nc_enddef(nc_id_O);
    CheckNCError(status);

    // Defines radials_structures
    if(containsRadial)
    {
      status = nc_redef(nc_id_O);
      CheckNCError(status);
      radial_structures_var_dims[0] = frame_dim_id_O;
      radial_structures_var_dims[1] = atom_dim_id_O;
      radial_structures_var_dims[2] = 
            radial_structure_function_dim_id_O;
      status = nc_def_var(nc_id_O, "radial_structures", NC_FLOAT, 3,
            radial_structures_var_dims, &radial_structures_var_id_O); 
      CheckNCError(status);
      status = nc_enddef(nc_id_O);
      CheckNCError(status);
    }

    // Defines angular_structures
    if(containsAngular)
    {
      status = nc_redef(nc_id_O);
      CheckNCError(status);
      angular_structures_var_dims[0] = frame_dim_id_O;
      angular_structures_var_dims[1] = atom_dim_id_O;
      angular_structures_var_dims[2] = 
            angular_structure_function_dim_id_O;
      status = nc_def_var(nc_id_O, "angular_structures", NC_FLOAT, 3,
            angular_structures_var_dims, &angular_structures_var_id_O);
      CheckNCError(status);
      status = nc_enddef(nc_id_O);
      CheckNCError(status);
    }
  }

  // Writes radial structure functions to frame f
  if(containsRadial)
  {
    idx_rad[0] = f;
    for(int pp=0; pp<n_p; pp++)
    {
      idx_rad[1] = pp;
      for(int SF=0; SF<n_SF_rad; SF++)
      {
        idx_rad[2] = SF;
        status = nc_put_var1_double(nc_id_O, 
              radial_structures_var_id_O, idx_rad, &SFs_radial[pp][SF]);
        CheckNCError(status);
      }
    }
  }

  // Writes angular structure functions to frame f
  if(containsAngular)
  {
    idx_ang[0] = f;
    for(int pp=0; pp<n_p; pp++)
    {
      idx_ang[1] = pp;
      for(int SF=0; SF<n_SF_ang; SF++)
      {
        idx_ang[2] = SF;
        status = nc_put_var1_double(nc_id_O, 
              angular_structures_var_id_O, idx_ang, 
              &SFs_angular[pp][SF]);
        CheckNCError(status);
      }
    }
  }

  writeSF = true;
}
