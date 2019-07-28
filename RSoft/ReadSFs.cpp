#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <string.h>

// Reads structure functions from frame f in RIGGLEMAN_STANDARD format
// Parameters:
//   f: int for frame containing data
// Outputs:
//   None
void RSoft::ReadSFs(int f)
{

  // Ensures that correct functions have been run before writing
  // netCDF file
  if(!openSFI)
  {
    std::cout << "ERROR: Must use OpenSFI before ReadSF\n";
    std::cout << std::flush;
    std::exit(-1);
  }
  if(not containsParticles)
  {
    std::cout << "ERROR: RSoftSF file must contain particles if";
    std::cout << " ReadSFs is used\n";
    std::exit(-1);
  }
  
  // Initializes c arrays
  static size_t idx_rad[3], idx_ang[3];
  char dim_name[NC_MAX_NAME+1];
  double SF_radial, SF_angular;
  unsigned long int dim_length;
  int n_dim, n_var, n_att, id_unlimited;

  // Defines variables to store structure functions if writeSF has not
  // been used before
  if(not readSF)
  {
    // Gets number of dimensions, variables, and attributes
    status = nc_inq(nc_id_I, &n_dim, &n_var, &n_att, &id_unlimited);
    CheckNCError(status);

    // Gets n_p and n_f
    for(int dim=0; dim<n_dim; dim++)
    {
      status = nc_inq_dim(nc_id_I, dim, dim_name, &dim_length);
      CheckNCError(status);
      if(strcmp(dim_name,"atom") == 0)
      {
        atom_dim_id_I = dim;
        n_p = (int) dim_length;
      }
      if(strcmp(dim_name,"frame") == 0)
      {
        frame_dim_id_I = dim;
        n_f = (int) dim_length;
      }
    }

    status = nc_inq_varid(nc_id_I, "radial_structures", 
          &radial_structures_var_id_I);
    CheckNCError(status);
    status = nc_inq_varid(nc_id_I, "angular_structures", 
          &angular_structures_var_id_I);
    CheckNCError(status);
  }

  // NOTE: this error warning must be placed after n_f found!
  if(f<0 || f>=n_f)
  {
    std::cout << "ERROR: Frame f = " << f << " is out of range! Must";
    std::cout << " be int in range [0,n_f) where n_f = " << n_f;
    std::cout <<  "\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Gets structure functions from frame f
  if(containsRadial)
  {
    // Initializes SFs_radial vector of vectors and other preliminary
    // information
    calculateRadialSFs = true;
    SFs_radial.resize(n_p);
    for(int pp=0; pp<n_p; pp++)
    {
      SFs_radial[pp].resize(n_SF_rad);
      std::fill(SFs_radial[pp].begin(), SFs_radial[pp].end(), 0);
    }

    // Fills SFs_radial with data
    idx_rad[0] = f;
    for(int pp=0; pp<n_p; pp++)
    {
      idx_rad[1] = pp;
      for(int SF=0; SF<n_SF_rad; SF++)
      {
        idx_rad[2] = SF;
        status = nc_get_var1_double(nc_id_I, radial_structures_var_id_I, 
              idx_rad, &SF_radial);
        CheckNCError(status);
        SFs_radial[pp][SF] += SF_radial;
      }
    }
  }

  // Gets structure functions from frame f
  if(containsAngular)
  {
    // Initializes SFs_angular vector of vectors and other preliminary
    // information
    calculateAngularSFs = true;
    SFs_angular.resize(n_p);
    for(int pp=0; pp<n_p; pp++)
    {
      SFs_angular[pp].resize(n_SF_ang);
      std::fill(SFs_angular[pp].begin(), SFs_angular[pp].end(), 0);
    }

    // Fills SFs_angular with data
    idx_ang[0] = f;
    for(int pp=0; pp<n_p; pp++)
    {
      idx_rad[1] = pp;
      for(int SF=0; SF<n_SF_ang; SF++)
      {
        idx_rad[2] = SF;
        status = nc_get_var1_double(nc_id_I, angular_structures_var_id_I,
            idx_ang, &SF_angular);
        CheckNCError(status);
        SFs_angular[pp][SF] += SF_angular;
      }
    }
  }

  readSF = true;
}
