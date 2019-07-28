#include "NetCDFIO.hpp"


void NetCDFIO::SetBB(int f, std::vector< std::vector<double> >& bb_t)
{

	static size_t idx[2];
	double var_origin;
	double var_length;
	double var_angles;

	if(d==-1)
	{
		d = bb_t.size();
		SetDimAtt();
	}

	// Define the variable. The type of the variable in this case is
	// NC_INT (4-byte integer).
	for (int dd=0; dd<3; dd++)
	{
		idx[0] = f;
		idx[1] = dd;

		if(dd!=d)
		{
			var_origin = bb_t[dd][0];
			var_length = bb_t[dd][1] - bb_t[dd][0];
			var_angles = 90.;
		}
		else
		{
			var_origin = -0.000001;
			var_length = 0.000002;
			var_angles = 90.;
		}


		status = nc_put_var1_double(nc_id, cell_origin_var_id, idx, &var_origin);
		if (status != NC_NOERR)
			ReportErr(status);
		status = nc_put_var1_double(nc_id, cell_lengths_var_id, idx, &var_length);
		if (status != NC_NOERR)
			ReportErr(status);
		status = nc_put_var1_double(nc_id, cell_angles_var_id, idx, &var_angles);
		if (status != NC_NOERR)
			ReportErr(status);


	}

	run_SetBB = true;

}

