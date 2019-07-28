#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <string.h>

// Imports RSoftSF file
// Parameters:
//   nc_file: std::string containing netcdf file name to grab input
// Outputs:
//   None
void RSoft::OpenSFI(std::string nc_file)
{

  // Error messages
  if(openSFI)
  {
    std::cout << "ERROR: Cannot use OpenSFI twice\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(openPlaneI)
  {
    std::cout << "ERROR: Cannot use OpenSFI and OpenPlaneI together\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Initializes variables for file opening
  char dim_name[NC_MAX_NAME+1];
  char conv_str[7];
  unsigned long int n_f_unsigned, n_p_unsigned;
  unsigned long int dim_length;
  int n_dim, n_var, n_att, id_unlimited;
  n_SF_rad = 0;  // These two lines are added here because these are 
  n_SF_ang = 0;  // not initialized properly in RSoft for some reason

  // Creates the file. Overwrites previous netCDF file.
  status = nc_open(nc_file.c_str(), NC_NOWRITE, &nc_id_I);
  CheckNCError(status);

  // Gets number of dimensions, variables, and attributes
  status = nc_inq(nc_id_I, &n_dim, &n_var, &n_att, &id_unlimited);
  CheckNCError(status);

  // Checks conventions are correct
  status = nc_get_att_text(nc_id_I, NC_GLOBAL, "Conventions", conv_str);
  if(strcmp(conv_str,"RSoftSF") != 0 or status != NC_NOERR)
  {
    std::cout << "ERROR: OpenSFI can only load RSoftSF files\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Gets number of dimensions, variables, and attributes
  status = nc_inq(nc_id_I, &n_dim, &n_var, &n_att, &id_unlimited);
  CheckNCError(status);

  // Gets structure function parameters from nc_id_I
  GetSFParams();

  // Loads evaluated structure function dimensions (if available)
  for(int dim=0; dim<n_dim; dim++)
  {
    status = nc_inq_dim(nc_id_I, dim, dim_name, &dim_length);
    CheckNCError(status);

    // Checks if dimension is frame
    if(strcmp(dim_name,"frame") == 0)
    {
      // Preliminary information about dimension
      containsParticles = true;
      frame_dim_id_I = dim;
      n_f_unsigned = dim_length;
      n_f = (int) n_f_unsigned;
    }

    // Checks if dimension is atom
    if(strcmp(dim_name,"atom") == 0)
    {
      // Preliminary information about dimension
      containsParticles = true;
      atom_dim_id_I = dim;
      n_p_unsigned = dim_length;
      n_p = (int) n_p_unsigned;
    }

  }

  // If output file has been opened,  writes structure function 
  // parameters immediately.
  if(openSFO)
  {
    SetSFParams();
  }

  // Marks program has run
  openSFI = true;  

}
