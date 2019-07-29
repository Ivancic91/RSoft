#include "RSoft.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// Checks if netCDF error has occured after performing operation
// Parameters:
//   None
// Outputs:
//   None
// NetCDF variables
#define ERRCODE 2
void RSoft::CheckNCError(int status)
{

  if (status != NC_NOERR)
  {
    printf("Error: %s\n", nc_strerror(status));
    exit(ERRCODE);
  }


}
