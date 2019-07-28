#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

void RSoft::CloseSFO()
{

  // Ensures netCDF file has been opened.
  if(!openSFO)
  {
    std::cout << "ERROR: Must use OpenSFO before CloseSFO\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Close the file. This frees up any internal netCDF resources
  // associated with the file, and flushes any buffers.
  status = nc_close(nc_id_O);
  CheckNCError(status);

  // Says netCDF file is closed.
  closeSFO = true;
  openSFO = false;

}
