#include <iostream>
#include <cassert>
#include "NetCDFIO.hpp"

void NetCDFIO::SetDataCol(int f, std::string label, std::vector<double>& data_col_t)
{

  // Initialization
  double var;
  int dc_var_id;
  static size_t idx[2];
  int col = -1;

  // Sets dimension
  if(n_p==-1)
  {
    n_p = data_col_t.size();
    SetAtomDim();
  }

  // Finds data column
  for(int dc=0; dc<n_dc; dc++)
  {
    if(label.compare(data_col_labels[dc])==0)
    {
      col = dc;
    }
  }

  // If have no column found, add a new column variable
  if(col == -1)
  {
    SetDataColVar(label);
    data_col_labels.push_back(label);
    col = data_col_var_ids.size() - 1;
    n_dc++;
  }

  // Finds data column id
  dc_var_id = data_col_var_ids[col];

  // Define the variable. The type of the variable in this case is
  // NC_INT (4-byte integer).
  for (int p=0; p<n_p; p++)
  {
    idx[0] = f;
    idx[1] = p;
    var = data_col_t[p];

    status = nc_put_var1_double(nc_id, dc_var_id, idx, &var);
    if (status != NC_NOERR)
      ReportErr(status);
  }

  run_SetPos = true;

}

void NetCDFIO::SetDataCol(int f, std::string label, std::vector<int>& data_col_t)
{

  // Initialization
  int var;
  int dc_var_id;
  static size_t idx[2];
  int col = -1;

  // Sets dimension
  if(n_p==-1)
  {
    n_p = data_col_t.size();
    SetAtomDim();
  }

  // Finds data column
  for(int dc=0; dc<n_dc; dc++)
  {
    if(label.compare(data_col_labels[dc])==0)
    {
      col = dc;
    }
  }

  // If have no column found, add a new column variable
  if(col == -1)
  {
    SetDataColVar(label,true);
    data_col_labels.push_back(label);
    col = data_col_var_ids.size() - 1;
    n_dc++;
  }

  // Finds data column id
  dc_var_id = data_col_var_ids[col];

  // Define the variable. The type of the variable in this case is
  // NC_INT (4-byte integer).
  for (int p=0; p<n_p; p++)
  {
    idx[0] = f;
    idx[1] = p;
    var = data_col_t[p];

    status = nc_put_var1_int(nc_id, dc_var_id, idx, &var);
    if (status != NC_NOERR)
      ReportErr(status);
  }

  run_SetPos = true;

}
