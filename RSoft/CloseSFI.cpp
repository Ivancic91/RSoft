#include "RSoft.hpp"
#include <iostream>
#include <cstdlib>

void RSoft::CloseSFI()
{

  // Ensures netCDF file has been opened.
  if(!openSFI)
  {
    std::cout << "ERROR: Must use OpenSFI before CloseSFI\n";
    std::cout << std::flush;
    std::exit(-1);
  }

  // Close the file. This frees up any internal netCDF resources
  // associated with the file, and flushes any buffers.
  status = nc_close(nc_id_I);
  CheckNCError(status);

  // Says netCDF file is closed.
  closeSFI = true;
  openSFI = false;

}
