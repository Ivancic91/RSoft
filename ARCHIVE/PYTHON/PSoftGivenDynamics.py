"""
WARNING: if you have missing particles in your dynamics file. This 
script will only work correctly if their type is marked nan when they
are missing (not just their position). 
"""
import numpy as np
from LammpsIO import NetCDFIO

# Sets some variables for script
str_dynamics = 'phop_test.nc'
str_dynamics_data_col = 'phop'
str_soft = 'soft_test.nc'     # This softness file needs to correspond
str_soft_data_col = 'S'       # to the str_dynamics file.
log10_low = np.log10(5*10**(-3))
log10_hi = np.log10(0.5)
n_bins = 40
n_type = 2
str_out = 'P_soft_given_phop_type'
cut_off_dynamics = 0.2

# Creates separate plot for each type
for type_ in range(1, n_type+1):
  # Opens dynamics and softness files
  nc_soft, nc_dynamics = NetCDFIO(), NetCDFIO()
  nc_soft.OpenI(str_soft)
  nc_dynamics.OpenI(str_dynamics)

  # Initializes variables for calculation
  log10_bin_edges = np.linspace(log10_low,log10_hi,num=n_bins)
  hist_sum = np.zeros(log10_bin_edges.shape[0]-1)
  hist_soft_sum = np.zeros(log10_bin_edges.shape[0]-1)
  n_rearrange = 0
  n_soft = 0
  n_soft_rearrange = 0
  n_p = 0

  for f in range(nc_soft.NumFrames()):
    # Gets data from AMBER files
    type_t = nc_dynamics.GetDataCol(f,'type')
    idx_type_ = np.where(type_t==type_)[0]
    dynamics_t = np.log10(nc_dynamics.GetDataCol(f,\
          str_dynamics_data_col)[idx_type_])
    S_t = nc_soft.GetDataCol(f,str_soft_data_col)[idx_type_]

    # Generates histogram
    hist, bin_edges = np.histogram(dynamics_t,bins=log10_bin_edges)
    hist_soft, bin_edges = np.histogram(dynamics_t[S_t>0], \
          bins=log10_bin_edges)
    hist_sum += hist
    hist_soft_sum += hist_soft

    #if type_==2:
    #  print(len(np.where(S_t>0)[0]))
    #  print(hist_sum)
    #  print(hist_soft_sum)
    #  print('----------')

    # Generates probabilities
    idx_R = np.where(10**dynamics_t > cut_off_dynamics)[0]
    n_rearrange += len(idx_R)
    n_soft += len(np.where(S_t > 0)[0])
    n_soft_rearrange += len(np.where(S_t[idx_R] > 0)[0])
    n_p += len(idx_type_)

  # Does error propogation. Obtains output array.
  bin_centers = 10**(0.5*(log10_bin_edges[1:]+log10_bin_edges[:-1]))
  PSgivenDynamics = hist_soft_sum/hist_sum
  err = np.sqrt(hist_sum+hist_sum**2/np.sum(hist_sum))
  err_soft = np.sqrt(hist_soft_sum+\
        hist_soft_sum**2/np.sum(hist_soft_sum))
  err_prop = PSgivenDynamics*np.sqrt((err/hist_sum)**2+\
        (err_soft/hist_soft_sum)**2)
  out = np.vstack((bin_centers,PSgivenDynamics,err_prop)).T

  # Outputs data for type
  np.savetxt(str_out+str(type_)+'.dat', out)

  # Prints
  print('TYPE = '+str(type_))
  print('  Percentage of rearranging particles that are soft:')
  print('  P(S>0|R) = '+str(n_soft_rearrange/n_rearrange))
  print('  Percentage of particles that are soft:')
  print('  P(S>0) = '+str(n_soft/n_p))

