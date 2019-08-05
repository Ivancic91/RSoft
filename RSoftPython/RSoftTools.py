# =*= coding: utf-8 -*-
"""RSoftTools
Created on 8 November 2018
@author: Robert Ivancic

This module was created to facilitate easy creation of softness
fields based on current methodologies. 

Notes
-----
  

"""

import numpy as np
import sys
from netCDF4 import Dataset
from LammpsIO import NetCDFIO
import sklearn as skl
from sklearn import svm

class RSoft:
  """RSoft package for python.

  This class is made to deal with and generate RSoftSF and RSoftPlane
  files.

  Attributes
  ----------
  etol_radial : float
    \epsilon_R

    Radial error tolerance (if available). Can obtain after OpenSFI.
  mus : numpy array (n_SF_rad)
    Mu structure function parameters (if available). Can obtain after
    OpenSFI used.
  radial_Xs : numpy int array (n_SF_rad)
    Radial_X structure function parameters (if available). Can obtain
    after OpenSFI used.
  radial_Ys : numpy int array (n_SF_rad)
    Radial_Y structure function parameters (if available). Can obtain
    after OpenSFI used.
  etol_angular : float
    Angular error tolerance (if available). Can obtain after OpenSFI.
  xis : numpy array (n_SF_ang)
    Xi structure function parameters (if available). Can obtain after
    OpenSFI used.
  lambdas : numpy int array (n_SF_ang)
    Lambda structure function parameters (if available). Can obtain
    after OpenSFI used.
  zetas : numpy int array (n_SF_ang)
    Zeta structure function parameters (if available). Can obtain
    after OpenSFI used.
  angular_Xs : numpy int array (n_SF_ang)
    Angular_X structure function parameters (if available). Can obtain
    after OpenSFI used.
  angular_Ys : numpy int array (n_SF_ang)
    Angular_Y structure function parameters (if available). Can obtain
    after OpenSFI used.
  angular_Zs : numpy int array (n_SF_ang)
    Angular_Z structure function parameters (if available). Can obtain
    after OpenSFI used.
  training_R : list (n_type) of numpy int array (n_eg_type, 2)
    Python list containing a numpy array containing the frame and 
    particle id (respectively) for each rearranging training example
    for each type of particle. Can obtain after SelectTrainingSet
    is used.
  training_NR : list (n_type) of numpy int array (n_eg_type, 2)
    Python list containing a numpy array containing the frame and 
    particle id (respectively) for each non-rearranging training
    example for each type of particle. Can obtain after 
    SelectTrainingSet is used.


  """

  def __init__(self):
    # Initializes private variables
    self.__containsRadial = False
    self.__containsAngular = False
    self.__containsParticles = False
    self.__n_SF_ang = 0
    self.__n_SF_rad = 0

    # Checks if public functions have been used
    self.__openSFI = False
    self.__openSFO = False
    self.__openPlaneI = False
    self.__openPlaneO = False
    self.__openDynamicsI = False
    self.__selectTrainingSet = False
    self.__train = False
    self.__getRadial = False
    self.__getAngular = False
    self.__setRadial = False
    self.__setAngular = False

    # SoftPlane global variable initialization
    self.__close = False

  def OpenSFO(self, nc_file_name):
    """ Opens RSoftSF file
    
    Opens a RSoftSF file of nc_file_name for writing (output).

    Parameters
    ----------
    nc_file_name : str
      Name of RSoftSF file you wish to write to.

    """
    # Checks errors
    if self.__openSFO:
      print('ERROR: Cannot use OpenSFO twice')
      sys.exit(-1)
    if self.__openPlaneO:
      print('ERROR: Cannot use OpenPlaneO and OpenSFO')
      sys.exit(-1)

    # Opens RSoftSF and initializes values
    self.__nc_RSoft_O = Dataset(nc_file_name, 'w', format='NETCDF4')
    self.__nc_RSoft_O.Conventions = 'RSoftSF'
    self.__nc_RSoft_O.ConventionVersion = '1.0'
    self.__SetSFParams()

    # Marks function as run
    self.__openSFO = True

    # Allows for chained statements
    return self

  def OpenPlaneO(self, nc_file_name):
    """ Opens RSoftPlane file
    
    Opens a RSoftPlane file of nc_file_name for writing (output).

    Parameters
    ----------
    nc_file_name : str
      Name of RSoftPlane file you wish to write to.

    """
    # Checks errors
    if self.__openPlaneO:
      print('ERROR: Cannot use OpenPlaneO twice')
      sys.exit(-1)
    if self.__openSFO:
      print('ERROR: Cannot use OpenSFO and OpenPlaneO')
      sys.exit(-1)

    # Opens RSoftPlane and initializes values
    self.__nc_RSoft_O = Dataset(nc_file_name, 'w', format='NETCDF4')
    self.__nc_RSoft_O.Conventions = 'RSoftPlane'
    self.__nc_RSoft_O.ConventionVersion = '1.0'
    self.__SetSFParams()

    # Marks function as run
    self.__openPlaneO = True

    # Allows for chained statements
    return self

  def OpenSFI(self, nc_file_name):
    """Opens RSoftSF file
    
    Opens a RSoftSF file of nc_file_name for reading (input).

    Parameters
    ----------
    nc_file_name : str
      Name of RSoftSF file you wish to read from.

    """
    # Checks errors
    if self.__openSFI:
      print('ERROR: Cannot use OpenSFI twice')
      sys.exit(-1)
    if self.__openPlaneI:
      print('ERROR: Cannot use OpenSFI and OpenPlaneI together')
      sys.exit(-1)

    # Opens RSoftSF and initializes values
    self.__nc_RSoft_I = Dataset(nc_file_name, 'r', format='NETCDF4')
    if self.__nc_RSoft_I.Conventions != 'RSoftSF':
      print('ERROR: OpenSFI can only load RSoftSF files')
    self.__GetSFParams()
    dim_names = list(self.__nc_RSoft_I.dimensions.keys())
    if 'frame' in dim_names:
      self.__containsParticles = True
    if self.__openSFO or self.__openPlaneO:
      self.__SetSFParams()

    # Error messages
    if self.__openDynamicsI and self.__containsParticles:
      if self._n_f != self.__nc_RSoft_I.dimensions['frame'].size:
        print('ERROR: n_f for RSoftSF and AMBER file are equal.')
        sys.exit(-1)
      if self._n_p != self.__nc_RSoft_I.dimensions['atom'].size:
        print('ERROR: n_p for RSoftSF and AMBER file are equal.')
        sys.exit(-1)

    # Obtains number of types of particles to make planes for
    self.__types = np.concatenate((self.radial_Xs, self.angular_Xs))
    self.__types_unique = np.unique(self.__types)
    self.__n_type = len(self.__types_unique)

    # Marks function as run
    self.__openSFI = True

    # Allows for chained statements
    return self

  def __GetSFParams(self):
    """Gets structure function parameters from nc_RSoft_I

    Reads all of the parameters used to calculate structure functions
    from an RSoftPlane or RSoftSF file.

    """

    dim_names = list(self.__nc_RSoft_I.dimensions.keys())
    if 'radial_structure_functions' in dim_names:
      self.__containsRadial = True
      self.__n_SF_rad = len(self.__nc_RSoft_I.variables['mus'][:])
      self.etol_radial = self.__nc_RSoft_I.radial_error_tolerance
      self.mus = self.__nc_RSoft_I.variables['mus'][:]
      self.Ls = self.__nc_RSoft_I.variables['Ls'][:]
      self.radial_Xs = self.__nc_RSoft_I.variables['radial_Xs'][:]
      self.radial_Ys = self.__nc_RSoft_I.variables['radial_Ys'][:]
    if 'angular_structure_functions' in dim_names:
      self.__containsAngular = True
      self.etol_angular = self.__nc_RSoft_I.angular_error_tolerance
      self.__n_SF_ang = len(self.__nc_RSoft_I.variables['xis'][:])
      self.xis = self.__nc_RSoft_I.variables['xis'][:]
      self.zetas = self.__nc_RSoft_I.variables['zetas'][:]
      self.lambdas = self.__nc_RSoft_I.variables['lambdas'][:]
      self.angular_Xs = self.__nc_RSoft_I.variables['angular_Xs'][:]
      self.angular_Ys = self.__nc_RSoft_I.variables['angular_Ys'][:]
      self.angular_Zs = self.__nc_RSoft_I.variables['angular_Zs'][:]

  def __SetSFParams(self):
    """Sets structure function parameters to nc_RSoft_O

    Writes all of the parameters used to calculate structure functions
    to an RSoftPlane or RSoftSF file.

    """

    # If radial structure functions are in output
    if self.__containsRadial:
      # Defines radial attributes
      self.__nc_RSoft_O.radial_error_tolerance = self.etol_radial

      # Defines radial dimensions
      self.__nc_RSoft_O.createDimension('radial_structure_functions',\
            len(self.mus))

      # Defines radial variables
      mus_var_id_O = self.__nc_RSoft_O.createVariable('mus', \
            'f4', ('radial_structure_functions'))
      Ls_var_id_O = self.__nc_RSoft_O.createVariable('Ls', \
            'f4', ('radial_structure_functions'))
      radial_Xs_var_id_O = self.__nc_RSoft_O.createVariable(\
            'radial_Xs', 'i4', ('radial_structure_functions'))
      radial_Ys_var_id_O = self.__nc_RSoft_O.createVariable(\
            'radial_Ys', 'i4', ('radial_structure_functions'))

      # Sets radial structure function variables
      mus_var_id_O[:] = self.mus
      Ls_var_id_O[:] = self.Ls
      radial_Xs_var_id_O[:] = self.radial_Xs
      radial_Ys_var_id_O[:] = self.radial_Ys

    # If angular structure functions are in output
    if self.__containsAngular:
      # Defines angular attributes
      self.__nc_RSoft_O.angular_error_tolerance = self.etol_angular

      # Defines angular dimensions
      self.__nc_RSoft_O.createDimension('angular_structure_functions',\
            len(self.xis))

      # Defines angular variables
      xis_var_id_O = self.__nc_RSoft_O.createVariable('xis', \
            'f4', ('angular_structure_functions'))
      zetas_var_id_O = self.__nc_RSoft_O.createVariable('zetas', \
            'i4', ('angular_structure_functions'))
      lambdas_var_id_O = self.__nc_RSoft_O.createVariable('lambdas', \
            'i4', ('angular_structure_functions'))
      angular_Xs_var_id_O = self.__nc_RSoft_O.createVariable(\
            'angular_Xs', 'i4', ('angular_structure_functions'))
      angular_Ys_var_id_O = self.__nc_RSoft_O.createVariable(\
            'angular_Ys', 'i4', ('angular_structure_functions'))
      angular_Zs_var_id_O = self.__nc_RSoft_O.createVariable(\
            'angular_Zs', 'i4', ('angular_structure_functions'))    

      # Sets angular structure function variables
      xis_var_id_O[:] = self.xis
      zetas_var_id_O[:] = self.zetas
      lambdas_var_id_O[:] = self.lambdas
      angular_Xs_var_id_O[:] = self.angular_Xs
      angular_Ys_var_id_O[:] = self.angular_Ys
      angular_Zs_var_id_O[:] = self.angular_Zs


  def OpenDynamicsI(self, nc_file_name, dynamics_name):
    """Opens dynamic file in AMBER (netCDF) file format
    
    Opens an AMBER molecular dynamics file. This file must have a data
    column named dynamics_name. This data column should contain p_hop 
    or D^2_min data to classify rearrangements or non-rearrangements in
    the system.

    Parameters
    ----------
    nc_file_name : str
      Name of AMBER file you wish to read from.
    dynamics_name : str
      Name of dynamics data column

    """

    # Checks errors
    if self.__openDynamicsI:
      print('ERROR: Cannot use OpenDynamicI twice')
      sys.exit(-1)


    # Opens AMBER file and checks for dynamics_name
    self.__NcIO_dyn = NetCDFIO()
    self.__NcIO_dyn.OpenI(nc_file_name)
    self._n_p = self.__NcIO_dyn.NumParts()
    self._n_f = self.__NcIO_dyn.NumFrames()
    try:
      self.__NcIO_dyn.GetDataCol(0,dynamics_name)
      self.__dynamics_name = dynamics_name
    except:
      print('ERROR: \''+dynamics_name+'\' data column is not in ')
      print('      '+nc_file_name)
      sys.exit(-1)
    try:
      self.__NcIO_dyn.GetDataCol(0,'type')
    except:
      print('ERROR: \'type\' data column is not in ' + nc_file_name)
      sys.exit(-1)

    # Error messages
    if self.__openSFI and self.__containsParticles:
      if self._n_f != self.__nc_RSoft_I.dimensions['frame'].size:
        print('ERROR: n_f for RSoftSF and AMBER file are equal.')
        sys.exit(-1)
      if self._n_p != self.__nc_RSoft_I.dimensions['atom'].size:
        print('ERROR: n_p for RSoftSF and AMBER file are equal.')
        sys.exit(-1)

    # Marks function as run
    self.__openDynamicsI = True

    # Allows for chained statements
    return self

  def Train(self, n_eg=None, K=5, \
          C_parameters=np.array([0.01, 0.1, 1.0, 10., 100.]), \
          norm_SF=True, norm_plane=True, tol_=0.0001, \
          max_iter_=10000):
    """ Trains a softness hyperplane

    Trains a softness hyperplane for all species given an RSoftSF file
    and an AMBER molecular dynamics file containing dynamics_name
    data column.

    Parameters
    ----------
    n_eg : numpy int array (n_types), optional
      Numpy array with number of rearranging training examples to 
      include for each type. If not set, assumes this to be maximum
      number which meets all other criteria
    K : int, optional
      Positive integer of folds for K-folds cross-validation to chooose
      optimal penalty parameter. K = 5 is used by default.
    C_parameters : numpy array, optional
      Numpy array of penalty parameters to test during 
      cross-validation. Values 0.01, 0.1, 1, 10, and 100 are default
      values to check.
    norm_SF : boolean, optional
      Whether to normalize structure functions before running linear
      SVM. This typically leads to better fits. If true, we subtract
      the mean and divide by the STDev of all structure functions. If
      not set, default is True.
    norm_plane : boolean, optional
      Ensures the standard deviation of softness is 1. If not set,
      default is true.

    """
    # ERROR messages
    if not self.__openSFI:
      print('ERROR: Must use OpenSFI before Train')
      sys.exit(-1)
    if not self.__containsParticles:
      print('ERROR: RSoftSF file must contain particles')
      sys.exit(-1)
    if not self.__openDynamicsI:
      print('ERROR: Must use OpenDynamicsI before Train')
      sys.exit(-1)
    if not self.__selectTrainingSet:
      print('ERROR: Must use SelectTrainingSet before Train')
      sys.exit(-1)

    # Initialize outputs
    self.radial_plane = np.zeros((self.__n_type, self.__n_SF_rad))
    self.angular_plane = np.zeros((self.__n_type, self.__n_SF_ang))
    self.intercept = np.zeros(self.__n_type)
    n_SF = self.__n_SF_rad + self.__n_SF_ang

    # Initialization of structure function and plane norms
    if not self.__train:
      self.__InitializeNorms(norm_SF, norm_plane)
    if norm_SF:
      mean_SF = self._mean_SF
      std_SF = self._std_SF
    else:
      mean_SF = np.zeros(n_SF)
      std_SF = np.ones(n_SF)

    # For each particle type
    for idx_type, type_ in enumerate(self.__types_unique):
      # Initializes model and grid search
      linear_svm = svm.LinearSVC(\
            dual=False, tol=tol_, max_iter=max_iter_)
      grid_search = skl.model_selection.GridSearchCV(linear_svm,
            param_grid={'C':C_parameters}, cv=K,
            refit=True)

      # Obtains particles used for training
      idx_type_SF = np.where(self.__types==type_)[0]
      particles_R = skl.utils.shuffle(self.training_R[idx_type])
      particles_NR = skl.utils.shuffle(self.training_NR[idx_type])
      if n_eg is None:
        n_eg_type = min(len(particles_R), len(particles_NR))
      else:
        n_eg_type = n_eg[idx_type]
      particles_R = particles_R[:n_eg_type]
      particles_NR = particles_NR[:n_eg_type]
      training_particles = np.concatenate([particles_R, particles_NR])

      # Obtains structure functions (X) and targets (Y) for training
      mean_SF_type = mean_SF[idx_type_SF]
      std_SF_type = std_SF[idx_type_SF]
      X_full = self._ParticlesToSFs(training_particles)
      X_type = (X_full[:,idx_type_SF]-mean_SF_type)/std_SF_type
      Y = np.concatenate((np.ones(n_eg_type), np.zeros(n_eg_type)))

      # Trains plane and stores results
      grid_search.fit(X_type, Y)
      plane = grid_search.best_estimator_.coef_[0]
      intercept = grid_search.best_estimator_.intercept_[0]

      # Converts from normalized SFs to un-normalized
      plane = plane / std_SF_type
      intercept = intercept - np.dot(plane,mean_SF_type)

      # Normalizes plane so that sofness has an std of 1
      if norm_plane:
        a = np.dot(plane,np.dot(self._cov_SF,plane))
        plane /= np.sqrt(a)
        intercept /= np.sqrt(a)

      # Stores results
      if self.__containsRadial:
        idx_type_SF_rad = np.where(self.radial_Xs==type_)[0]
        self.radial_plane[idx_type, idx_type_SF_rad] = \
              plane[:self.__n_SF_rad]
      if self.__containsAngular:
        idx_type_SF_ang = np.where(self.angular_Xs==type_)[0]
        self.angular_plane[idx_type, idx_type_SF_ang] = \
              plane[-self.__n_SF_ang:]
      self.intercept[idx_type] = intercept

    # Marks program as run
    self.__train = True

    # Allows for chained statements
    return self

  def __InitializeNorms(self, norm_SF, norm_plane):
    """ Initializes normalization or structure functions or planes

    Initializes the parameters __mean_SF, __std_SF, and __covList.

    Parameters
    ----------
    norm_SF : boolean, optional
      Whether to normalize structure functions before running linear
      SVM. This typically leads to better fits. If true, we subtract
      the mean and divide by the STDev of all structure functions. If
      not set, default is True.
    norm_plane : boolean, optional
      Ensures the standard deviation of softness is 1. If not set,
      default is true.

    """
    # Initializes values    
    nc = self.__nc_RSoft_I
    n_SF = self.__n_SF_rad+self.__n_SF_ang
    mean_SF = np.zeros(n_SF)
    std_SF = np.zeros(n_SF)
    cov_SF = np.zeros((n_SF,n_SF))
    n_parts = 0

    for idx_type, type_ in enumerate(self.__types_unique):
      idx_type_SF = np.where(self.__types==type_)[0]
      for f in range(self._n_f):
        # Finds particle typtes for each particle. 
        particle_types = self.__NcIO_dyn.GetDataCol(f,'type')
        type_ids = np.where(particle_types==type_)[0]

        # Obtains radial and angular SFs for f
        if self.__containsRadial:
          rSF = nc.variables['radial_structures'][f][type_ids]
        else:
          rSF = np.zeros((len(type_ids),0))
        if self.__containsAngular:
          aSF = nc.variables['angular_structures'][f][type_ids]
        else:
          aSF = np.zeros((len(type_ids),0))
        SF = np.hstack((rSF,aSF))

        # Counts number of SFs in frame and sums particles to find
        # mean. We do not use nanmean function in case number of 
        # particles changes between frames
        n_parts += np.count_nonzero(~np.isnan(SF[:,0]))
        mean_SF += np.nansum(SF,axis=0)
        cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] += \
              np.dot(SF.T,SF)
      
      # Calculates mean and covariance
      mean_SF[idx_type_SF] /= float(n_parts)
      cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] /= \
            float(n_parts)
      cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] -= \
            np.outer(mean_SF[idx_type_SF],mean_SF[idx_type_SF])
      std_SF = np.sqrt(np.diagonal(cov_SF))

      self._mean_SF = mean_SF
      self._cov_SF = cov_SF
      self._std_SF = std_SF

  def _ParticlesToSFs(self, particles):
    """ Converts particle frames and ids to structure functions

    Obtains structure functions of all particles in the particles
    array.

    Parameters
    ----------
    particles : numpy int array (n_particles, 2)
      An array containing the frames and particle ids of particles to
      obtain structure functions. First column is for frame and second
      is for particle id.

    """
    particles = particles.astype(int)
    nc = self.__nc_RSoft_I
    n_particles = len(particles)
    n_SF = self.__n_SF_rad+self.__n_SF_ang
    SFs = np.zeros((n_particles, n_SF))
    for idx, particle in enumerate(particles):
      f = particle[0]
      p = particle[1]
      if self.__containsRadial:
        rSF = nc.variables['radial_structures'][f][p]
      else:
        rSF = np.zeros(self.__n_SF_rad)
      if self.__containsAngular:
        aSF = nc.variables['angular_structures'][f][p]
      else:
        aSF = np.zeros(self.__n_SF_ang)
      SFs[idx] = np.concatenate((rSF,aSF))
    return SFs

  def SelectTrainingSet(self, rearrangement_cutoff, \
        non_rearrangement_frames = None, \
        non_rearrangement_cutoff = None, str_mask = None):
    """ Selects training set

    Selects the training set from the dynamic AMBER file. 

    Parameters
    ----------
    rearrangement_cutoff : numpy array (n_types)
      Numpy array with a rearrangement cutoff for the dynamical 
      quantity in data column of AMBER dynamical file.
    non_rearrangement_frames : numpy int array (n_types), optional
      Numpy array of frames for a particle not to rearrange before 
      being counted as part of non-rearranging training set for each 
      particle type. If not set, assumes 0 frames for each particle 
      type, i.e. instantaneously less than non_rearrangement_cutoff.
    non_rearrangement_cutoff : numpy array (n_types), optional
      Numpy array with a non-rearrangement cutoff for the dynamical
      quantity in data column of AMBER dynamical file. If not set,
      uses the rearrangement_cutoff.
    str_mask : str, optional
      Name of the data column of AMBER dynamic file corresponding to 
      a mask of 0's and 1's in which 1's are particles that may be
      included in training set and 0's cannot.

    """
    # Initializes parameters
    dynamics_name = self.__dynamics_name
    self.training_R = []
    self.training_NR = []

    # If non_rearrangement_cutoff not set, chooses it to be 
    # rearrangement_cutoff
    if non_rearrangement_cutoff is None:
      non_rearrangement_cutoff = rearrangement_cutoff
    if non_rearrangement_frames is None:
      non_rearrangement_frames = np.zeros(self.__n_type)

    # for each type finds rearranging and non-rearranging cutoffs
    for idx_type, type_ in enumerate(self.__types_unique):
      r_cut = rearrangement_cutoff[idx_type]
      nr_cut = non_rearrangement_cutoff[idx_type]
      n_nr_f = non_rearrangement_frames[idx_type]
      rs_arr_all = np.zeros((0,2))
      nrs_arr_all = np.zeros((0,2))
      for f in range(self._n_f):
        # obtains mask for all particles at frame f
        if str_mask is None:
          mask = np.ones(self._n_p).astype(bool)
        else:
          mask = self.__NcIO_dyn.GetDataCol(f,str_mask).astype(bool)

        # creates types mask
        particle_types = self.__NcIO_dyn.GetDataCol(f,'type')
        type_mask = np.where(particle_types==type_, True, False)

        # Finds rearranging particles at frame f
        dynamics_f = self.__NcIO_dyn.GetDataCol(f,dynamics_name)
        r_mask = np.where(dynamics_f > r_cut, True, False)
        rs_arr = np.where(mask*type_mask*r_mask)[0]
        f_arr = np.ones(len(rs_arr))*f
        rs_arr = np.vstack((f_arr, rs_arr)).T
        rs_arr_all = np.vstack((rs_arr_all, rs_arr))

        # Finds non-rearranging particles at frame f-n_nr_f/2
        if f == 0:
          dynamics_arr = np.array([dynamics_f])
        else:
          dynamics_arr = np.vstack((dynamics_arr, \
                  np.array([dynamics_f])))
        if f > n_nr_f:
          dynamics_arr = np.delete(dynamics_arr, 0, axis=0)
        if f >= n_nr_f:
          # Finds particles that have been below the non-rearranging
          # cutoff for previous n_nr_f frames.
          nr_mask = np.all(np.where(dynamics_arr<nr_cut, True, False),\
                axis=0)
          nrs_arr = np.where(mask*type_mask*nr_mask)[0]
          f_arr = np.ones(len(nrs_arr))*(f-int(n_nr_f/2))
          nrs_arr = np.vstack((f_arr, nrs_arr)).T
          nrs_arr_all = np.vstack((nrs_arr_all, nrs_arr))
      
      # Saves all rearranging and non-rearranging examples for frame
      self.training_R.append(rs_arr_all.astype(int))
      self.training_NR.append(nrs_arr_all.astype(int))
      
    self.__selectTrainingSet = True

  def WritePlane(self):
    """ Writes plane to RSoftPlane file

    """
    if not self.__train:
      print('ERROR: Must use Train before WritePlane')
      sys.exit(-1)
    if not self.__openPlaneO:
      print('ERROR: Must use OpenPlaneO before WritePlane')
      sys.exit(-1)

    # Defines angular dimensions
    self.__nc_RSoft_O.createDimension('type', self.__n_type)

    # Defines variables
    if self.__containsRadial:
      rad_plane_id = self.__nc_RSoft_O.createVariable(\
            'radial_plane', 'f4', \
            ('type','radial_structure_functions'))
      rad_plane_id[:] = self.radial_plane
    if self.__containsAngular:
      ang_plane_id = self.__nc_RSoft_O.createVariable(\
            'angular_plane', 'f4', \
            ('type','angular_structure_functions'))
      ang_plane_id[:] = self.angular_plane
    intercept_id_O = self.__nc_RSoft_O.createVariable(\
          'intercept', 'f4', ('type'))
    intercept_id_O[:] = self.intercept

  def GetRadial(self, f):
    """ Gets radial structure functions 

    Gets radial structure functions for frame f.

    Parameters
    ----------
    f : int
      Frame number to obtain radial structure functions

    """
    if not self.__openSFI:
      print('ERROR: Must use OpenSFI before GetRadial')
      sys.exit(-1)
    if self.__containsRadial:
      SF = self.__nc_RSoft_I.variables['radial_structures'][f][:]
    else:
      print('ERROR: RSoftSF input file does not contain radial')
      print('      structures')
      sys.exit(-1)

    # Marks as run
    self.__getRadial = True

    return SF

  def GetAngular(self, f):
    """ Gets angular structure functions 

    Gets angular structure functions for frame f.

    Parameters
    ----------
    f : int
      Frame number to obtain angular structure functions

    """
    if not self.__openSFI:
      print('ERROR: Must use OpenSFI before GetAngular')
      sys.exit(-1)
    if self.__containsAngular:
      SF = self.__nc_RSoft_I.variables['angular_structures'][f][:]
    else:
      print('ERROR: RSoftSF input file does not contain angular')
      print('      structures')
      sys.exit(-1)

    # Marks as run
    self.__getAngular = True

    return SF

  def SetRadial(self, f, SF):
    """ Sets radial structure functions 

    Sets radial structure functions for frame f.

    Parameters
    ----------
    f : int
      Frame number to set radial structure functions

    """
    if not self.__openSFO:
      print('ERROR: Must use OpenSFO before SetRadial')
      sys.exit(-1)

    # Creates dimensions and variables to hold structures
    if not self.__setRadial and not self.__setAngular:
      self.__nc_RSoft_O.createDimension('frame', 0)
      self.__nc_RSoft_O.createDimension('atom', SF.shape[0])
    if not self.__setRadial:
      self.__nc_RSoft_O.createDimension('radial_structure_functions',\
            SF.shape[1])
      self.__nc_RSoft_O_radial_structures = \
            self.__nc_RSoft_O.createVariable('radial_structures', \
            'f4', ('frame','atom','radial_structure_functions'))

    # Stores SFs
    self.__nc_RSoft_O_radial_structures[f] = SF

    # Marks as run
    self.__setRadial = True

  def SetAngular(self, f, SF):
    """ Sets angular structure functions 

    Sets angular structure functions for frame f.

    Parameters
    ----------
    f : int
      Frame number to set angular structure functions

    """
    if not self.__openSFO:
      print('ERROR: Must use OpenSFO before SetAngular')
      sys.exit(-1)

    # Creates dimensions and variables to hold structures
    if not self.__setRadial and not self.__setAngular:
      self.__nc_RSoft_O.createDimension('frame', 0)
      self.__nc_RSoft_O.createDimension('atom', SF.shape[0])
    if not self.__setAngular:
      self.__nc_RSoft_O.createDimension('radial_structure_functions',\
            SF.shape[1])
      self.__nc_RSoft_O_angular_structures = \
            self.__nc_RSoft_O.createVariable('angular_structures', \
            'f4', ('frame','atom','angular_structure_functions'))

    # Stores SFs
    self.__nc_RSoft_O_angular_structures[f] = SF

    # Marks as run
    self.__setAngular = True

  def CloseSFI(self):
    """ Closes input of RSoftSF file
    """
    self.__nc_RSoft_I.close()

  def CloseSFO(self):
    """ Closes output of RSoftSF
    """

  def CloseDynamicsI(self):  
    """ CLoses input of AMBER NetCDF dynamics file
    """
    self.__NcIO_dyn.CloseI()

  def ClosePlaneO(self):
    """ Closes output of RSoftPlane file
    """
    self.__nc_RSoft_O.close() 



class MDTools:
  """ Molecular Dynamics Tools for python

  This class is designed to provide some standard molecular dynamics
  tools to analyze trajectories.

  """

  def __init__(self):
    self.tmp = False

  def DeltaR(self, rf, ri, bb, bc):
    """ Difference between two vectors or sets of vectors
    
    Calculates the difference between two positions rf and ri (rf-ri) 
    with respect to the box boundaries (bb) and the boundary conditions
    (bc). The numpy arrays rf and ri can either be single particle
    positions or sets of particle positions. Let d = dimension of the
    space and N = number of vectors.

    Parameters
    ----------
    rf : numpy array, either (d) or (N, d)
      Final positions of particle(s) in d-dimensional space.
    ri : numpy array, either (d) or (N, d)
      Initial positions of particle(s) in d-dimensional space.
    bb : numpy array, (d, 2)
      Box boundaries of simulation or the experiment. For d=2, this
      should be formatted [[low_x, high_x],[low_y, high_y]]. In d=3,
      [[low_x, high_x],[low_y, high_y],[low_z, high_z]].
    bc : numpy str array, (d)
      Boundary conditions of the experiment or simulation. Each value
      must be a single character string denoting the boundary condition
      in each direction. 'p' means periodic boundary conditions. 's' 
      means shrink wrapped bounday conditions. 'f' means fixed boundary
      conditions.

    Returns
    -------
    dr : numpy array, either (d) or (N, d)
      The rf-ri given the box boundaries and boundary conditions.

    """

    # Checks if all dimensions are matching
    dim_f = rf.shape[-1]
    dim_i = ri.shape[-1]
    dim_bc = len(bc)
    dim_bb = bb.shape[0]
    if dim_f != dim_i or dim_f != dim_bc or dim_f != dim_bb:
      str_ = 'ERROR: dimension mismatch for rf, ri, bc, and'
      str_ += ' bb.shape[0]'
      sys.exit(str_)

    # Checks if rf and ri are vectors or vector of vectors
    arr_f_dim = len(rf.shape)
    arr_i_dim = len(ri.shape)

    # CASE: both rf and ri are vectors
    if arr_f_dim == 1 and arr_i_dim == 1:
      dr = rf - ri
      idx_p_arr = np.where(bc=='p')[0]
      for idx_p in idx_p_arr:
        L = bb[idx_p,1] - bb[idx_p,0]
        if dr[idx_p]>L/2: dr[idx_p] -= L
        if dr[idx_p]<-L/2: dr[idx_p] += L

    # CASE: rf or ri are vectors of vectors
    elif arr_f_dim == 2 and arr_i_dim == 1 or\
          arr_f_dim == 1 and arr_i_dim == 2 or\
          arr_f_dim == 2 and arr_i_dim == 2:

      # If rf and ri are vectors of vectors ensures they have
      # the same number of particles, N
      if arr_f_dim == 2 and arr_i_dim == 2:
        if rf.shape[0] != ri.shape[0]:
          str_ = 'ERROR: rf and ri don\'t have same number of '
          str_ += 'particles, N'
          sys.exit(str_)

      dr = rf - ri
      idx_p_arr = np.where(bc=='p')[0]
      for idx_p in idx_p_arr:
        L = bb[idx_p,1] - bb[idx_p,0]
        dr2 = dr
        dr[dr[:,idx_p]>L/2,idx_p] -= L
        dr[dr[:,idx_p]<-L/2,idx_p] += L

    # CASE: rf or ri are neither vectors or vectors of vectors
    else:
      sys.exit('ERROR: rf or ri are not vectors or vectors of vectors')

    return dr
            
  def GetNList(self, pos_t, bb_t, bc, R_c):
    """ Obtains a neighbor list for a set of particles

    Finds all of the neighbors within a cuttoff distance (R_c) for a 
    set of particles (pos_t) given a set of box boundaries (bb_t), and
    a set of boundary conditions.

    Parameters
    ----------
    pos_t : numpy array, (n_p, d)
      Set of n_p particle positions in d-dimensional space
    bb_t : numpy array, (d, 2)
      Box boundaries of simulation or the experiment. For d=2, this
      should be formatted [[low_x, high_x],[low_y, high_y]]. In d=3,
      [[low_x, high_x],[low_y, high_y],[low_z, high_z]].
    bc : numpy str array, (d)
      Boundary conditions of the experiment or simulation. Each value
      must be a single character string denoting the boundary condition
      in each direction. 'p' means periodic boundary conditions. 's' 
      means shrink wrapped bounday conditions. 'f' means fixed boundary
      conditions.
    R_c : float
      Cutoff radius of the simulation.

    Returns
    -------
    n_list : python array, (n_p)
      Python list in which n_list[i] is a numpy array of all neighbors
      of particle i from pos_t. 

    """

    # Initializes variables
    self.__R_c_2 = R_c*R_c
    self.__n_p = pos_t.shape[0]
    self.__d = pos_t.shape[1]
    self.__n_list_t = [[] for p in range(self.__n_p)]
    cell_delta_arr = self.__InitializeCellDeltaArr()

    # Bins particles into cells
    particles_in_cell = self.__BinParticlesIntoCells(pos_t, bb_t, R_c)
    n_cells_tot = len(particles_in_cell)

    for cell_idx in range(n_cells_tot):
      # Initializes shift
      shift = np.zeros(self.__d)

      # Adds neighbors from same cell
      self.__AddNeighbors(pos_t, particles_in_cell, R_c, shift,\
            cell_idx, cell_idx)
      cell_pos = self.__Unstack(cell_idx)

      # Adds neighbors from neighboring cells
      for cell_delta in cell_delta_arr:

        # checks if cells are neighbors
        are_neighbors, neigh_cell_pos, shift = self.__AddCellPos(\
                cell_pos, cell_delta, bb_t, bc)

        # if cells are neighbors, adds particles to neighbor list
        if are_neighbors:
          neigh_cell_idx = self.__Stack(neigh_cell_pos)
          self.__AddNeighbors(pos_t, particles_in_cell, R_c, shift,
                cell_idx, neigh_cell_idx)

    return self.__n_list_t

  def __InitializeCellDeltaArr(self):
    # determines list of neighoring cells
    if self.__d == 2:
      cell_delta_arr = np.array([\
            [-1,1], [0,1], [1,1], [1,0]])
    else:
      cell_delta_arr = np.array([\
            [-1,-1,1], [-1,0,1], [-1,1,1],\
            [0,-1,1], [0,0,1], [0,1,1],\
            [1,-1,1], [1,0,1], [1,1,1],\
            [-1,1,0], [0,1,0], [1,1,0],\
            [1,0,0]])
    return cell_delta_arr

  def __BinParticlesIntoCells(self, pos_t, bb_t, R_c):

    # Finds number of cells in each dimension and cell lengths
    L = (bb_t[:,1]-bb_t[:,0]).astype(float)
    self.__n_cells = (L/R_c).astype(int)
    self.__n_cells[self.__n_cells < 3] = 3
    self.__cell_lengths = L / self.__n_cells
    self.__n_cells_tot = np.prod(self.__n_cells)

    # Place particles in cells
    particles_in_cell = [[] for cells in range(self.__n_cells_tot)]
    cell_pos = ((pos_t-bb_t[:,0])/self.__cell_lengths).astype(int)
    cell_idx = self.__Stack(cell_pos)
    for pp in range(pos_t.shape[0]):
      particles_in_cell[cell_idx[pp]].append(pp)

    return particles_in_cell

  def __Stack(self, cell_pos):
    # CASE: cell_pos is a vector
    if len(cell_pos.shape)==1:
      if self.__d==2:
        n_x = self.__n_cells[0]
        cell_idx = cell_pos[0]+cell_pos[1]*n_x
      elif self.__d==3:
        n_x = self.__n_cells[0]
        n_y = self.__n_cells[1]
        cell_idx = cell_pos[0]+(cell_pos[1]+cell_pos[2]*n_x)*n_y

    # CASE cell_pos is a vector of vectors
    elif len(cell_pos.shape)==2:
      if self.__d==2:
        n_x = self.__n_cells[0]
        cell_idx = cell_pos[:,0]+cell_pos[:,1]*n_x
      elif self.__d==3:
        n_x = self.__n_cells[0]
        n_y = self.__n_cells[1]
        cell_idx = cell_pos[:,0]+(cell_pos[:,1]+cell_pos[:,2]*n_x)*n_y

    return cell_idx

  def __Unstack(self, cell_idx):
    if self.__d==2:
      n_x = self.__n_cells[0]
      y = int(cell_idx/n_x)
      x = int(cell_idx-y*n_x)
      cell_pos = np.array([x,y])
    elif self.__d==3:
      n_x = self.__n_cells[0]
      n_y = self.__n_cells[1]
      z = int(cell_idx/(n_x*n_y))
      y = int((cell_idx-z*n_x*n_y)/n_x)
      x = int((cell_idx-z*n_x*n_y-y*n_x))
      cell_pos = np.array([x,y,z])
    return cell_pos

  def __AddNeighbors(self, pos_t, particles_in_cell, R_c, shift,\
        cell_idx, neigh_cell_idx):
    n_p_cell = len(particles_in_cell[cell_idx])
    n_p_neigh_cell = len(particles_in_cell[neigh_cell_idx])

    for p_cell in range(n_p_cell):
      # Particle index
      p = particles_in_cell[cell_idx][p_cell];

      # Ensures no double counting
      if(cell_idx==neigh_cell_idx):
        n_p_neigh_cell = p_cell

      for p_neigh_cell in range(n_p_neigh_cell):
        # Neighboring particle index
        p_neigh = particles_in_cell[neigh_cell_idx][p_neigh_cell]

        r_vec = pos_t[p]-(pos_t[p_neigh]+shift)
        sq_sum = np.sum(r_vec*r_vec)
        if sq_sum<self.__R_c_2:
          self.__n_list_t[p].append(p_neigh)
          self.__n_list_t[p_neigh].append(p)

  def __AddCellPos(self, cell_pos, cell_delta, bb_t, bc):
    neigh_cell_pos = cell_pos + cell_delta
    shift = np.zeros(self.__d)
    are_neighbors = True
    for dd in range(self.__d): 
      if bc[dd] == 'p': 
        if neigh_cell_pos[dd]==-1:
          neigh_cell_pos[dd] = self.__n_cells[dd]-1
          shift[dd] = bb_t[dd][0]-bb_t[dd][1]
        elif neigh_cell_pos[dd]==self.__n_cells[dd]:
          neigh_cell_pos[dd] = 0
          shift[dd] = bb_t[dd][1]-bb_t[dd][0]
      else:
        if neigh_cell_pos[dd]==-1 or \
              neigh_cell_pos[dd]==self.__n_cells[dd]:
          are_neighbors = False

    return (are_neighbors, neigh_cell_pos, shift)





















