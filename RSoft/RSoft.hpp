/*
 * RSoft.hpp
 *
 *  Created on: October 15, 2018
 *      Author: Robert Ivancic
 */

#ifndef RSOFT_HPP_
#define RSOFT_HPP_

#include <vector> 
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// link_cpp netcdf DO NOT REMOVE THIS LINE
#include <netcdf.h>

class RSoft
{
private:

  // Variables
  bool openSFO, openSFI, openPlaneI;
  bool setPos, setBB, setBC, setType, setRadii;
  bool checkDim, checkNumParts, checkSets;
  bool getRadialSFs, getAngularSFs, getSoftness;
  bool calculateRadialSFs, calculateAngularSFs;
  bool writeSF, readSF;
  bool closeSFO, closeSFI, closePlaneI;
  bool containsRadial, containsAngular, containsParticles;
  int d, n_p, n_f, n_SF_rad, n_SF_ang, n_type;
  double etol_radial, etol_angular;
  double log_inv_etol_radial, log_inv_etol_angular;

  // Set variables
  std::vector< std::vector<double> > pos;
  std::vector< std::vector<double> > bb;
  std::vector< std::string > bc;
  std::vector<int> type;

  // Params variables
  std::vector<double> mus;
  std::vector<double> Ls;
  std::vector<int> radial_Xs;
  std::vector<int> radial_Ys;
  std::vector<double> xis;
  std::vector<int> zetas;
  std::vector<int> lambdas;
  std::vector<int> angular_Xs;
  std::vector<int> angular_Ys;
  std::vector<int> angular_Zs;
  std::vector<int> unique_angular_Xs;
  std::vector<int> unique_angular_Ys;
  std::vector<int> unique_angular_Zs;

  // Neighbor lists and r_ij lists
  std::vector< std::vector<int> > n_list_angular;
  std::vector< std::vector<double> > R_list_angular;
  std::vector< std::vector<int> > n_list_radial;
  std::vector< std::vector<double> > R_list_radial;

  // Structure function variables
  std::vector< std::vector<double> > SFs_radial;
  std::vector< std::vector<double> > SFs_angular;

  // Plane variables
  std::vector< std::vector<double> > radial_plane;
  std::vector< std::vector<double> > angular_plane;
  std::vector<double> intercept;

  // NetCDF ids for input
  int nc_id_I, status;
  int frame_dim_id_I, atom_dim_id_I, radial_structure_function_dim_id_I;
  int type_dim_id_I, radial_plane_id_I, angular_plane_id_I;
  int mus_var_id_I, Ls_var_id_I, radial_Xs_var_id_I, radial_Ys_var_id_I;
  int radial_structures_var_id_I, angular_structure_function_dim_id_I;
  int xis_var_id_I, zetas_var_id_I, lambdas_var_id_I;
  int angular_Xs_var_id_I, angular_Ys_var_id_I, angular_Zs_var_id_I;
  int angular_structures_var_id_I;
  int radial_plane_var_id_I, angular_plane_var_id_I, intercept_var_id_I;

  // NetCDF ids for output
  int nc_id_O;
  int frame_dim_id_O, atom_dim_id_O, radial_structure_function_dim_id_O;
  int type_dim_id_O, radial_plane_id_O, angular_plane_id_O;
  int mus_var_id_O, Ls_var_id_O, radial_Xs_var_id_O, radial_Ys_var_id_O;
  int radial_structures_var_id_O, angular_structure_function_dim_id_O;
  int xis_var_id_O, zetas_var_id_O, lambdas_var_id_O;
  int angular_Xs_var_id_O, angular_Ys_var_id_O, angular_Zs_var_id_O;
  int angular_structures_var_id_O;
  int radial_plane_var_id_O, angular_plane_var_id_O, intercept_var_id_O;

  // Functions
  void CheckNCError(int status); // Checks if netCDF error has occured
  void GetSFParams();            // Gets structure function parameters
  void SetSFParams();            // Sets structure function parameters
  void CheckDim(int d);          // Checks if d is consistent
  void CheckNumParts(int n_p);   // Checks if n_p is consistent 
  void CheckSets();              // Ensures all sets correct before calc
  void CalculateRadialSFs();     // Calculates radial SFs for all parts 
  void CalculateRadialSF_p_n(int pp, int nn);
                                 // Calculates radial SF between particle
                                 //     pp and neighbor nn
  void CalculateAngularSFs();    // Calculates radial SFs for all parts 
  void CalculateAngularSFs_p(
      int pp_i, 
      std::vector<int>& SF_idx_arr,
      std::vector<int>& n_list_j,
      std::vector<int>& n_list_k,
      bool IIeqJJ,
      bool IIeqKK,
      bool JJeqKK);
  //void CalculateAngularSF_p_n_sn(int pp, int nn, int sn);
                                 // Calculates angular SF between
                                 //     particle pp and neighbors
                                 //     nn and sn
  void CalculateNListRList();    // Calculates neighbor and
                                 //     corresponding R_ij list
  double GetRcRadial();          // Gets cutoff of radial SFs
  double GetRcAngular();         // Gets cutoff of angular SFs
  void ResetSets();

public:

  // Initializes private variables
  RSoft()
  {
    containsRadial = false;
    containsAngular = false;
    containsParticles = false;
    n_SF_rad = 0;  // These two lines do not work for some reason...
    n_SF_ang = 0;
    etol_radial = 0.01;
    etol_angular = 0.01;

    ///////////////////////////////////////////////////////////////////
    // Checks if public functions have been used
    ///////////////////////////////////////////////////////////////////
    openSFO = false;
    openSFI = false;
    openPlaneI = false;

    setPos = false;
    setBB = false;
    setBC = false;
    setType = false;

    getRadialSFs = false;
    getAngularSFs = false;
    getSoftness = false;

    writeSF = false;
    readSF = false;

    closeSFO = false;
    closeSFI = false;
    closePlaneI = false;

    ///////////////////////////////////////////////////////////////////
    // Checks if private functions have been used
    ///////////////////////////////////////////////////////////////////
    checkDim = false;
    checkNumParts = false;
    checkSets = false;
    calculateRadialSFs = false;
    calculateAngularSFs = false;

  }

  // Opens trajectory, structure function, or plane file
  void OpenSFO(std::string nc_file);
  void OpenSFI(std::string nc_file);
  void OpenPlaneI(std::string nc_file);

  // Sets various properties about frame
  void SetPos(std::vector< std::vector<double> >& pos_t);
  void SetBB(std::vector< std::vector<double> >& bb_t);
  void SetBC(std::vector< std::string >& bc_t);
  void SetType(std::vector<int>& type_t);

  // Gets radial structure functions, angular structure functions, and
  // softness of all particles given correct inputs.
  void GetRadialSFs(
        std::vector< std::vector<double> >& SFs);
  void GetAngularSFs(
        std::vector< std::vector<double> >& SFs);
  void GetSoftness(std::vector<double>& softness);
  void GetMus(std::vector<double>& mus);
  void GetLs(std::vector<double>& Ls);
  void GetRadialXs(std::vector<int>& type_Xs);
  void GetRadialYs(std::vector<int>& type_Ys);
  void GetRadialEtol(double& etol_rad);

  // Reads and writes structure functions given 
  void WriteSFs(int f);
  void ReadSFs(int f);

  // Closes structure function or plane file
  void CloseSFO();
  void CloseSFI();
  void ClosePlaneI();
  

}; 
#endif /* RSOFT_HPP_ */
