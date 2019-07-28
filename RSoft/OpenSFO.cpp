#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>
#include <string.h>

// Opens RSoftSF file for output
// Parameters:
//   nc_file: std::string containing netcdf file name to output to
// Outputs:
//   None
void RSoft::OpenSFO(std::string nc_file)
{
  // Error messages
  if(openSFO)
  {
    std::cout << "ERROR: Cannot use OpenSFO twice\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Creates the file. Overwrites previous netCDF file.
  status = nc_create(nc_file.c_str(), NC_CLOBBER, &nc_id_O);
  CheckNCError(status);
  status = nc_put_att_text(nc_id_O, NC_GLOBAL, "Conventions", 7, 
        "RSoftSF");
  CheckNCError(status);
  status = nc_put_att_text(nc_id_O, NC_GLOBAL, "ConventionVersion",
        3, "1.0");
  CheckNCError(status);

  // Ends definition
  status = nc_enddef(nc_id_O);
  CheckNCError(status);

  // If input file has been opened,  writes structure function 
  // parameters immediately.
  if(openSFI or openPlaneI)
  {
    SetSFParams();
  }

  // Marks program as run
  openSFO = true;

}
