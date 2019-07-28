#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

void RSoft::ClosePlaneI()
{

  // Ensures netCDF file has been opened.
  if(!openPlaneI)
  {
    std::cout << "ERROR: Must use OpenPlaneI before ClosePlaneI\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Close the file. This frees up any internal netCDF resources
  // associated with the file, and flushes any buffers.
  status = nc_close(nc_id_I);
  CheckNCError(status);

  // Says netCDF file is closed.
  closePlaneI = true;
  openPlaneI = false;

}
