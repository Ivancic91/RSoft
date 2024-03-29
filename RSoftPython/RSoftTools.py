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
from math import sqrt
from math import log

class RSoft:
  """RSoft package for python.

  This class is made to deal with and generate RSoftSF and RSoftPlane
  files.

  Attributes
  ----------
  etol_radial : float
    Radial error tolerance (if available). Can obtain after OpenSFI.
  mus : numpy array (n_SF_rad)
    Mu structure function parameters (if available). Can obtain after
    OpenSFI used.
  Ls : numpy array (n_SF_rad)
    L structure function parameters (if available). Can obtain after
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
    self.radial_Xs = np.array([])
    self.angular_Xs = np.array([])

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
      Name of RSoftPlane file you wish to write to.

    """
    # Checks errors
    if self.__openSFO:
      print('ERROR: Cannot use OpenSFO twice')
      sys.exit(-1)
    if self.__openPlaneO:
      print('ERROR: Cannot use OpenPlaneO and OpenSFO')
      sys.exit(-1)

    # Opens RSoftPlane and initializes values
    self.__nc_RSoft_O = Dataset(nc_file_name, 'w', format='NETCDF4')
    self.__nc_RSoft_O.Conventions = "RSoftSF"
    self.__nc_RSoft_O.ConventionVersion = "1.0"
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
        cov = self._cov_SF[idx_type_SF][:,idx_type_SF]
        np.savetxt('cov'+str(type_)+'.dat', cov)
        a = np.dot(plane,np.dot(cov,plane))
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
      n_parts = 0
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
        SF = SF[~np.isnan(np.sum(SF,axis=1))] # SHOULD REMOVE NaNs

        # Counts number of SFs in frame and sums particles to find
        # mean. We do not use mean function in case number of 
        # particles changes between frames
        n_parts += len(SF)
        mean_SF[idx_type_SF] += np.sum(SF[:,idx_type_SF],axis=0)
        cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] += \
              np.dot(SF[:,idx_type_SF].T,SF[:,idx_type_SF])

      # Calculates mean and covariance
      mean_SF[idx_type_SF] /= float(n_parts)
      cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] /= \
            float(n_parts)
      cov_SF[idx_type_SF[:,None],idx_type_SF[None,:]] -= \
            np.outer(mean_SF[idx_type_SF],mean_SF[idx_type_SF])
      std_SF = np.sqrt(np.diagonal(cov_SF))

    # Checks if std_SF == 0 for any structure functions
    if np.any(std_SF==0):
      print('WARNING: stdev of following structure functions is 0')
      idx_0s = np.where(std_SF==0)[0]
      for idx_0 in idx_0s:
        std_SF[idx_0] = 1
        if idx_0 < self.__n_SF_rad:
          mu = self.mus[idx_0]
          L = self.Ls[idx_0]
          X = self.radial_Xs[idx_0]
          Y = self.radial_Ys[idx_0]
          print('  radial structure function: mu = '+str(mu)+\
                ', L = '+str(L)+', X = '+str(X)+', Y = '+str(Y))
        else:
          idx_0 -= self.__n_SF_rad
          xi = self.xis[idx_0]
          l = self.lambdas[idx_0] 
          z = self.zetas[idx_0]
          X = self.angular_Xs[idx_0]
          Y = self.angular_Ys[idx_0]
          Z = self.angular_Za[idx_0]
          print('  angular structure function: xi = '+str(xi)+\
                ', lambda = '+str(l)+', zeta = '+str(z)+\
                ', X = '+str(X)+', Y = '+str(Y)+', Z = '+str(Z))

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
      self.__nc_RSoft_O_angular_structures = \
            self.__nc_RSoft_O.createVariable('angular_structures', \
            'f4', ('frame','atom','angular_structure_functions'))

    # Stores SFs
    self.__nc_RSoft_O_angular_structures[f] = SF

    # Marks as run
    self.__setAngular = True

  def CloseSFO(self):
    """ Closes RSoftSFO file
    """
    self.__nc_RSoft_O.close()

  def CloseSFI(self):
    """ Closes RSoftSFI file
    """
    self.__nc_RSoft_I.close()

  def CloseDynamicsI(self):  
    """ CLoses AMBER NetCDF dynamics file
    """
    self.__NcIO_dyn.CloseI()

  def ClosePlaneO(self):
    """ Closes RSoftPlaneO file
    """
    self.__nc_RSoft_O.close() 

  def Test(self, K_test=5, n_eg=None, K=5, \
          C_parameters=np.array([0.01, 0.1, 1.0, 10., 100.]), \
          norm_SF=True, norm_plane=True, tol_=0.0001, \
          max_iter_=10000):
    """ Tests a softness hyperplane

    Tests a softness hyperplane for all species given an RSoftSF file
    and an AMBER molecular dynamics file containing dynamics_name
    data column. Does this testing using stratified nested K-folds.

    Parameters
    ----------
    K_test : int, optional
      Positive integer of folds for nested K-folds cross-validation to 
      in test set. K_test = 5 is used by default.
    Descriptions of other parameters can be found in Train function


    Returns
    -------
    numpy array (n_type,3)
      Array that contains the test set accuracy, the test set accuracy
      of rearranging particles, and the test set accuracy of 
      non-rearranging particles.

    """

    # test acc array
    test_acc = np.zeros((self.__n_type, 3))
    n_test_eg = np.zeros((self.__n_type, 3))

    # Saving examples for real training later and shuffling examples
    for idx_type, type_ in enumerate(self.__types_unique):
      np.random.shuffle(self.training_R[idx_type])
      np.random.shuffle(self.training_NR[idx_type])
    training_R = list(self.training_R)
    training_NR = list(self.training_NR)


    for K_ in range(K_test):
      print('K = '+str(K_))

      # Creates a testing an training set from original training set
      testing_R = []
      testing_NR = []
      for idx_type, type_ in enumerate(self.__types_unique):

        # Finds rearrangements and non-rearrangements of given particle
        # type
        Rs_type = self.training_R[idx_type]
        NRs_type = self.training_NR[idx_type]

        # Finds a test set of rearrangements
        Rs_type_test = Rs_type[K_::K_test]
        NRs_type_test = NRs_type[K_::K_test]
        n_test = min(len(Rs_type_test),len(NRs_type_test))
        Rs_type_test = Rs_type_test[:n_test]
        NRs_type_test = NRs_type_test[:n_test]
        testing_R.append(Rs_type_test)
        testing_NR.append(NRs_type_test)

        # Deletes test set from training set
        Rs_type = np.delete(Rs_type, \
              list(range(K_,len(Rs_type),K_test)),axis=0)
        NRs_type = np.delete(NRs_type, \
              list(range(K_,len(NRs_type),K_test)), axis=0)
        self.training_R[idx_type] = Rs_type
        self.training_NR[idx_type] = NRs_type

      # Trains softness model using reduced training set
      self.Train(n_eg=n_eg, K=K, \
            C_parameters=C_parameters, norm_SF=norm_SF, \
            norm_plane=norm_plane, tol_=tol_, \
            max_iter_=max_iter_)

      # Tests new plane against test set
      for idx_type, type_ in enumerate(self.__types_unique):

        # Finds number of soft rearrangements and hard 
        # non-rearrangements
        soft_Rs = self.GetSoft(testing_R[idx_type])
        soft_NRs = self.GetSoft(testing_NR[idx_type])
        nRs = np.sum(soft_Rs > 0)
        nNRs = np.sum(soft_NRs < 0)

        # Calculates # of correctly classified particles
        test_acc[idx_type][0] += nRs+nNRs
        n_test_eg[idx_type][0] += len(soft_Rs)+len(soft_NRs)
        test_acc[idx_type][1] += nRs
        n_test_eg[idx_type][1] += len(soft_Rs)
        test_acc[idx_type][2] += nNRs
        n_test_eg[idx_type][2] += len(soft_NRs)

      # Returns self.training_R and self.training_NR to original state
      self.training_R = list(training_R)
      self.training_NR = list(training_NR)

    # Calculates test set accuracy
    test_acc = test_acc / n_test_eg

    return test_acc

  def GetSoft(self, particles):
    """ Gets softness of a set of particles

    Finds the softness of a set of particles, i.e. either an array of 
    particles frames and labels or all particles in a given frame.

    Parameters
    ----------
    particles : numpy array (n_eg, 2)
      Numpy array where each row is a particle, the first column 
      represents the particle frame, and the second column is the 
      particle id or an int describing the frame of which to get all
      particle softnesses

    Returns
    -------
    numpy array
      Numpy array in which each value is a softness value of the
      particles given.

    """

    if not self.__openSFI:
      print('ERROR: Must use OpenSFI before GetSoft.')
      sys.exit(-1)
    if not self.__containsParticles:
      print('ERROR: RSoftSF file must contain particles to use this')
      print('      file.')
      sys.exit(-1)

    # Obtains structure functions
    SFs = self._ParticlesToSFs(particles)


    soft_arr = np.zeros(len(particles))
    for idx_particle, particle in enumerate(particles):

      f = particle[0]
      p = particle[1]
      type_ = self.__NcIO_dyn.GetDataCol(f,'type')[p]
      idx_type = np.where(type_==self.__types_unique)[0]

      # Loads plane (a) and intercept (b)
      if self.__containsRadial:
        a_rad = self.radial_plane[idx_type]
      if self.__containsAngular:
        a_ang = self.angular_plane[idx_type]
      else:
        a_ang = np.array([])
      a = np.hstack((a_rad,a_ang))
      b = self.intercept[idx_type]

      # Calculates softness
      soft_arr[idx_particle] = np.dot(a,SFs[idx_particle])+b

    return soft_arr


  def SetRSoftSF(self, etol_rad = None, mus = None, Ls = None, \
        radial_Xs = None, radial_Ys = None, etol_ang = None, \
        xis = None, lambdas = None, zetas = None, angular_Xs = None, \
        angular_Ys = None, angular_Zs = None):
    """ Sets RSoft structure functions

    Sets RSoftSF structure function parameters for computation. Checks
    parameters are valid if not throws an error. Also, prints out the
    cutoff radius Rc of the structure funcions being used. 

    Parameters
    ----------
    etol_rad : float, optional
      Error tolerance for the radial structure functions 
      0 < etol_rad < 1
    mus : numpy array (n_SF_rad), optional
      mu parameters for all radial structure functions
    Ls : numpy array (n_SF_rad), optional
      L parameters for all radial structure functions
    radial_Xs : numpy int array (n_SF_rad), optional
      Integer particle type labels (X) for all radial structure 
      functions
    radial_Ys : numpy int array (n_SF_rad), optional
      Integer particle type labels (Y) for all radial structure 
      functions
    etol_ang : float, optional
      Error tolerance for the angular structure functions 
      0 < etol_ang < 1
    xis : numpy array (n_SF_rad), optional
      xi parameters for all angular structure functions
    lambdas : numpy int array (n_SF_rad), optional
      lambda parameters for all angular structure functions. Must be 
      +/-1
    zetas : numpy int array (n_SF_rad), optional
      zeta parameters for all angular structure functions.
    angular_Xs : numpy int array (n_SF_rad), optional
      Integer particle type labels (X) for all angular structure 
      functions
    angular_Ys : numpy int array (n_SF_rad), optional
      Integer particle type labels (Y) for all angular structure 
      functions
    angular_Zs : numpy int array (n_SF_rad), optional
      Integer particle type labels (Z) for all angular structure 
      functions

    """
    # Initializes global cutoff radius
    Rc_global = 0

    # Checks if any radial inputs used. If so, if any parameters are 
    # not None then throws an error assuming the user is confused. 
    # Checks all inputs are valid.
    if any(v is None for v in [etol_rad, mus, Ls, radial_Xs, radial_Ys]):
      if any(v is not None for v in (etol_rad, mus, Ls, radial_Xs, \
            radial_Ys)):
        print('ERROR: If radial structure functions are used, must ')
        print('      supply etol_rad, mus, Ls, radial_Xs, radial_Ys ')
        print('      to SetRSoftSF')
        sys.exit(-1)
    else:
     
      # Marks that it contains radial structure functions
      self.__containsRadial = True 

      # Initializes radial structure function variables
      if etol_rad > 0 and etol_rad < 1: 
        self.etol_radial = etol_rad
      else:
        print('ERROR: 0 < etol_rad < 1 used in SetRSoftSF')
        sys.exit(-1)
      if any(len(mus) != len(arr) for arr in (Ls, radial_Xs, \
            radial_Ys)):
        print('ERROR: Length of mus, radial_Xs, and radial_Ys in ')
        print('      SetRSoftSF must be equal')
        sys.exit(-1)
      self.mus = mus
      self.Ls = Ls 
      if np.all(np.mod(radial_Xs,1)==0):
        self.radial_Xs = radial_Xs.astype(int)
      else:
        print('ERROR: radial_Xs used in SetRSoftSF must be integers')
        sys.exit(-1)
      if np.all(np.mod(radial_Ys,1)==0):
        self.radial_Ys = radial_Ys.astype(int)
      else:
        print('ERROR: radial_Ys used in SetRSoftSF must be integers')
        sys.exit(-1)

      # Outputs radial cut-off radii
      print('Calculating radial cutoff...')
      Rc_max = 0.0
      for SF in range(len(mus)):
        mu = mus[SF]
        L = Ls[SF]
        X = radial_Xs[SF]
        Y = radial_Ys[SF]
        Rc = mu+L*sqrt(log(1/etol_rad))
        print('  mu='+str(mu)+', L='+str(L)+', X='+str(X)+', Y='+\
              str(Y)+' --> Rc='+str(Rc))
        if Rc > Rc_max:
          Rc_max = Rc 
      print('Rc_radial='+str(Rc_max))
      print(' ')
      print('--------------------------------------------------------')
      if Rc_max > Rc_global:
        Rc_global = Rc_max

    # Checks if any angular inputs used. If so, if any parameters are 
    # not None then throws an error assuming the user is confused. 
    # Checks all inputs are valid.
    if any(v is None for v in [etol_ang, xis, lambdas, angular_Xs, 
          angular_Ys, angular_Zs]):
      if any(v is not None for v in (etol_ang, xis, lambdas, zetas, \
            angular_Xs, angular_Ys, angular_Zs)):
        print('ERROR: If angular structure functions are used, must ')
        print('      supply etol_ang, xis, lambdas, zetas, angular_Xs,')
        print('      angular_Ys, angular_Zs')
        print('      to SetRSoftSF')
        sys.exit(-1)
    else:

      # Marks that contains angular structure functions
      self.__containsAngular = True 

      # Initializes angular structure function variables
      if etol_ang > 0 and etol_ang < 1: 
        self.etol_angular = etol_ang
      else:
        print('ERROR: 0 < etol_ang < 1 used in SetRSoftSF')
        sys.exit(-1)
      if any(len(xis) != len(arr) for arr in (lambdas, zetas, \
            angular_Xs, angular_Ys, angular_Zs)):
        print('ERROR: Length of xis, zetas, angular_Xs, angular_Ys, ')
        print('      and angular_Zs in SetRSoftSF must be equal')
        sys.exit(-1)
      self.xis = xis
      if np.all(np.abs(lambdas)==1):
        self.lambdas = lambdas
      else:
        print('ERROR: lambdas used in SetRSoftSF must be +/-1')
        sys.exit(-1)
      if np.all(np.mod(zetas,1)==0):
        self.zetas = zetas.astype(int)
      else:
        print('ERROR: angular_Xs used in SetRSoftSF must be integers')
        sys.exit(-1)
      if np.all(np.mod(angular_Xs,1)==0):
        self.angular_Xs = angular_Xs.astype(int)
      else:
        print('ERROR: angular_Xs used in SetRSoftSF must be integers')
        sys.exit(-1)
      if np.all(np.mod(angular_Ys,1)==0):
        self.angular_Ys = angular_Ys.astype(int)
      else:
        print('ERROR: angular_Ys used in SetRSoftSF must be integers')
        sys.exit(-1)
      if np.all(np.mod(angular_Zs,1)==0):
        self.angular_Zs = angular_Zs.astype(int)
      else:
        print('ERROR: angular_Zs used in SetRSoftSF must be integers')
        sys.exit(-1)

      # Outputs radial cut-off radii
      print('Calculating angular cutoff...')
      Rc_max = 0.0
      for SF in range(len(xis)):
        xi = xis[SF]
        l = lambdas[SF]
        zeta = zetas[SF]
        X = angular_Xs[SF]
        Y = angular_Ys[SF]
        Z = angular_Zs[SF]
        if l==1:
          Rc = xi*sqrt(2.0*log(1.0/etol_ang)/3.0)
        else:
          Rc = xi*sqrt(log(1.0/etol_ang)/2.0)
        print('  xi='+str(xi)+', lambda='+str(l)+', zeta='+str(zeta)+\
              ', X='+str(X)+', Y='+str(Y)+', Z='+str(Z)+' --> Rc='+str(Rc))
        if Rc > Rc_max:
          Rc_max = Rc 
      print('Rc_angular='+str(Rc_max))
      print(' ')
      print('--------------------------------------------------------')
      if Rc_max > Rc_global:
        Rc_global = Rc_max

    # Sets structure functions into netCDF file
    self.__SetSFParams()

    print('Rc='+str(Rc_global))





















