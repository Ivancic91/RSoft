#include "NetCDFIO.hpp"
#include <stdlib.h>

void NetCDFIO::DefineGlobalAttributes()
{

	// Defines c strings for all attribute headers/labels
	char const* conventions_att_label = "Conventions";
	char const* my_convention_att_label = "AMBER";
	char const* convention_ver_att_label = "ConventionVersion";
	char const* my_convention_ver_att_label = "1.0";
	char const* program_att_label = "program";
	char const* my_program_att_label = "RobIsAwesome.cpp";
	char const* program_ver_att_label = "programVersion";
	char const* my_program_ver_att_label = "1.0";

    status = nc_redef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

    // Global Attributes for AMBER
    status = nc_put_att_text(
    		nc_id, NC_GLOBAL, conventions_att_label,
    		strlen(my_convention_att_label), my_convention_att_label);
    if (status != NC_NOERR)
    	ReportErr(status);
    status = nc_put_att_text(
    		nc_id, NC_GLOBAL, convention_ver_att_label,
    		strlen(my_convention_ver_att_label), my_convention_ver_att_label);
    if (status != NC_NOERR)
    	ReportErr(status);
    status = nc_put_att_text(
    		nc_id, NC_GLOBAL, program_att_label,
    		strlen(my_program_att_label), my_program_att_label);
    if (status != NC_NOERR)
    	ReportErr(status);
    status = nc_put_att_text(
    		nc_id, NC_GLOBAL, program_ver_att_label,
    		strlen(my_program_ver_att_label), my_program_ver_att_label);
    if (status != NC_NOERR)
    	ReportErr(status);

    status = nc_enddef(nc_id);
    if (status != NC_NOERR)
    	ReportErr(status);

}
