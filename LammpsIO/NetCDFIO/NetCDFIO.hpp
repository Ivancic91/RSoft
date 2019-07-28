/*
 * NetCDFIO.hpp
 *
 *  Created on: Sep 26, 2016
 *      Author: Robert
 */

#ifndef NETCDFIO_HPP_
#define NETCDFIO_HPP_
#include <string>
#include <vector>
#include <netcdf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class NetCDFIO
{
private:

  // NetCDF vars
  int nc_id, status;

  int frame_dim_id, spatial_dim_id, atom_dim_id;          //netCDF ids for dims
  int cell_spatial_dim_id, cell_angular_dim_id, label_dim_id;

  int char_spatial_var_dims[1];              //netCDF ids for var dimensions
  int char_cell_spatial_var_dims[1];
  int char_cell_angular_var_dims[2];
  int time_var_dims[1];
  int cell_origin_var_dims[2];
  int cell_lengths_var_dims[2];
  int cell_angles_var_dims[2];
  int coordinates_var_dims[3];
  int dc_var_dims[2];

  int char_spatial_var_id, char_cell_spatial_var_id; //netCDF ids for vars
  int char_cell_angular_var_id, time_var_id;
  int cell_origin_var_id, cell_lengths_var_id;
  int cell_angles_var_id, coordinates_var_id;
  int dc_var_id;

  // NetCDF error handling
  #define ERRCODE 2
  void ReportErr(int e) {printf("Error: %s\n", nc_strerror(e)); exit(ERRCODE);}

  // Input variables
  //-----------------------------------------------------//

  int d;                                    // Dimension of space
  int n_p;                                  // Number of particles
  int n_f;                                  // Number of frames
  int n_dc;                                 // Number of data columns

  bool run_SetPos;
  bool run_SetData;
  bool run_SetBB;

  std::vector<std::string> data_col_labels;
  std::vector<int> data_col_var_ids;

  void OpenNCO(std::string nc_file_name);
  void DefineGlobalAttributes();
  void DefineDimensions();
  void DefineVariables();
  void SetLabelVariables();
  void SetAtomDim();
  void SetDimAtt();
  void SetPosVar();
  void SetDataColVar(std::string label, bool is_int = false);

public:

  void OpenO(std::string nc_file_name);
  void Sett(int f, int t);
  void SetBB(int f, std::vector< std::vector<double> >& bb_t);
  void SetPos(int f, std::vector< std::vector<double> >& pos_t);
  void SetDataCol(int f, std::string label, std::vector<double>& data_col_);
  void SetDataCol(int f, std::string label, std::vector<int>& data_col_);
  void CloseO();

  void OpenI(std::string nc_file_name);
  int NumDims();
  int NumFrames();
  int NumParts();
  void Gett(int f, int t);
  void GetBB(int f, std::vector< std::vector<double> >& bb_t);
  void GetPos(int f, std::vector< std::vector<double> >& pos_t);
  void GetDataCol(int f, std::string label, std::vector<double>& data_col_);
  void GetDataCol(int f, std::string label, std::vector<int>& data_col_);
  void CloseI();



};




#endif /* NETCDFIO_HPP_ */
