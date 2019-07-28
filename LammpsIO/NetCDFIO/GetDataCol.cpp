#include "NetCDFIO.hpp"

void NetCDFIO::GetDataCol(int f, std::string label, std::vector<double>& data_col_)
{

  char const* dc_var_label = label.c_str();
  static size_t idx[2];
  double var;

  d = NumDims();
  n_p = NumParts();

  // Clears out previous pos_t values
  data_col_.clear();

  status = nc_inq_varid(nc_id, dc_var_label, &dc_var_id);
  if (status != NC_NOERR)
    ReportErr(status);

  for(int p=0; p<n_p; p++)
  {

    idx[0] = f;
    idx[1] = p;

    status = nc_get_var1_double(nc_id, dc_var_id, idx, &var);
    if (status != NC_NOERR)
      ReportErr(status);

    data_col_.push_back(var);

    }

}

void NetCDFIO::GetDataCol(int f, std::string label, std::vector<int>& data_col_)
{

  char const* dc_var_label = label.c_str();
  static size_t idx[2];
  int var;

  d = NumDims();
  n_p = NumParts();

  // Clears out previous pos_t values
  data_col_.clear();

  status = nc_inq_varid(nc_id, dc_var_label, &dc_var_id);
  if (status != NC_NOERR)
    ReportErr(status);

  for(int p=0; p<n_p; p++)
  {

    idx[0] = f;
    idx[1] = p;

    status = nc_get_var1_int(nc_id, dc_var_id, idx, &var);
    if (status != NC_NOERR)
      ReportErr(status);

    data_col_.push_back(var);

  }   

}

