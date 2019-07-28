/*
 * LammpsIO.hpp
 *
 *  Created on: Sep 20, 2016
 *      Author: Robert
 */

#ifndef DUMPIO_HPP_
#define DUMPIO_HPP_

#include <vector>
#include <string>
#include <stdlib.h>

class DumpIO
{
private:

  // Shared variables
  //-----------------------------------------------------//
  int d;            // Dimension of space
  int n_f;          // Number of frames
  int n_dc;         // Number of data columns
  int n_p;          // Number of particles

  bool run_input;   // Has run OpenI dump
  bool run_output;  // Has run OpenO dump

  // labels corresponding to data columns
  std::vector< std::string > data_cols_labels;

  // ids corresponding to particles at t
  std::vector< int > id_t;

  // box boundary time t
  std::vector< std::vector<double> > bb_t;

  // positions corresponding to particles at t
  std::vector< std::vector<double> > pos_t;

  // data columns at t
  std::vector< std::vector<double> > data_col_t;

  // Input variables
  //-----------------------------------------------------//
  bool run_LoadHeader;            // Has run LoadHeader
  bool run_AnalyzeItemAtomsLine;  // Has run AnalyzeItemAtomsLine
  bool run_LoadNextFrame;		    // Has run LoadNextFrame
  bool found_id;					// Has found ID in dump
  bool found_timestep;            // Has found timestep in dump
  bool found_data_col;            // Has found data columns in dump
  bool found_num_parts;           // Has found the number of particles
  bool found_box_bounds;          // Has found box boundaries

  int current_f;    // current frame
  int t;            // current timestep
  int col_x;        // x column
  int col_y;        // y column
  int col_z;        // z column
  int col_id;       // id column

  // Initializes parameters for inputting dump file.
  void InitializeParameters();

  // Finds the next element in a space separated list
  int NextElem(const std::string& line, int start, std::string& elem);

  // Loads all header values
  void LoadHeader(std::ifstream& read_dump);

  // Analyzes Item: ATOMS to find:
  //     (a) x, y, and z columns
  //     (b) id columns (if there)
  //     (c) data columns (if there)
  void AnalyzeItemAtomsLine(std::ifstream& read_dump);

  // Reads all atom positions, ids, and data columns
  void LoadAtomData(std::ifstream& read_dump);

  // Output variables
  //-----------------------------------------------------//
  bool set_t;                       // Tag for having obtained t
  bool set_bb;                      // Tag for having obtained box bounds
  bool set_id;                      // Tag for having obtained ids
  bool set_pos;                     // Tag for having obtained positions
  bool set_dc;                      // Tag for having obtained a data column

  // Initializes parameters for outputting dump file.
  void InitializeWriteParameters();

  // Initializes parameters for outputting dump file
  void WriteItemAtoms(std::ofstream& write_dump);

public:

  void OpenI(std::ifstream& read_dump);
  int NumDims(std::ifstream& read_dump);
  int NumFrames(std::ifstream& read_dump);
  int NumPartsCurrentf(std::ifstream& read_dump);
  int NumDataCols(std::ifstream& read_dump);
  void LoadNextFrame(std::ifstream& read_dump);

  void Getf(int& f_);
  void Gett(int& t_);
  void GetBB(std::vector< std::vector<double> >& bb_t_);
  void GetID(std::vector<int>& id_t_);
  void GetPos(std::vector< std::vector<double> >& pos_t_);
  void GetDataColLabels(std::vector<std::string>& data_cols_labels_);
  void GetDataCol(std::string label, std::vector<double>& data_t_);
  void GetDataCol(std::string label, std::vector<int>& data_t_);
  void SortByID();

  void OpenO(std::ofstream& write_dump);
  void WriteNextFrame(std::ofstream& write_dump);
  void Sett(int t_);
  void SetBB(std::vector< std::vector<double> >& bb_t_);
  void SetID(std::vector<int>& id_t_);
  void SetPos(std::vector< std::vector<double> >& pos_t_);
  void SetDataCol(std::string label, std::vector<double>& data_t_);
  void SetDataCol(std::string label, std::vector<int>& data_t_);

};


#endif /* LAMMPSIO_HPP_ */


