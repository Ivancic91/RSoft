#include "NetCDFIO.hpp"

/*
 *  Opens netcdf file in AMBER format.
 */
void NetCDFIO::OpenO(std::string nc_file_name)
{
	run_SetPos = false;
	run_SetData = false;
	run_SetBB = false;

	d = -1;
	n_p = -1;
	n_f = -1;
	n_dc = 0;

	OpenNCO(nc_file_name);

    // Defines convention, convention version, program, and program version
    DefineGlobalAttributes();

    // Defines the dimensions NetCDF will hand back an ID for each.
    DefineDimensions();

    // Defines all variables
    DefineVariables();

    // Sets basic AMBER variables
    SetLabelVariables();


}

