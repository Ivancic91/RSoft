#include "NetCDFIO.hpp"
#include "../../VectorTools/VectorTools.hpp"

void NetCDFIO::GetBB(int f, std::vector< std::vector<double> >& bb_t)
{

	d = NumDims();

	VectorTools vtool;
	char const* cell_origin_var_label = "cell_origin";
	char const* cell_lengths_var_label = "cell_lengths";
	static size_t idx[2];
	double var_origin, var_length;
	std::vector<double> bb_t_dd(2);

	// Clears out previous bb_t values
	vtool.Clear2DVec(bb_t);

	status = nc_inq_varid(nc_id, cell_origin_var_label, &cell_origin_var_id);
    if (status != NC_NOERR)
    	ReportErr(status);
	status = nc_inq_varid(nc_id, cell_lengths_var_label, &cell_lengths_var_id);
    if (status != NC_NOERR)
    	ReportErr(status);

	for (int dd=0; dd<d; dd++)
	{
		idx[0] = f;
		idx[1] = dd;

		status = nc_get_var1_double(nc_id, cell_origin_var_id, idx, &var_origin);
		if (status != NC_NOERR)
			ReportErr(status);
		status = nc_get_var1_double(nc_id, cell_lengths_var_id, idx, &var_length);
		if (status != NC_NOERR)
			ReportErr(status);


		bb_t_dd[0] = var_origin;
		bb_t_dd[1] = var_origin + var_length;
		bb_t.push_back(bb_t_dd);

	}

}
