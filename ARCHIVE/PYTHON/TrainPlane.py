# train_plane is a script designed to generate an RSoftPlane file 
# for a 10,000 particle system with 10,000 frames I expect this to
# take 1 hour to run
from RSoftTools import RSoft
import random
import numpy as np
from LammpsIO import NetCDFIO
import time

# Initializes RSoft object
rs = RSoft()

# Opens files for input and output
name_rSoftSF = 'phop.SF.nc'
name_MD = 'phop.nc'
name_Dynamics = 'phop'
name_plane = 'KA.plane.nc'       
r_cut = np.array([0.2,0.2])      # phop cutoff for rearrangements (r's)
nr_frames = np.array([500,500])  # number of frames below non-r threshold
nr_cut = np.array([0.05,0.05])   # non-r threshold for each type
#n_train = np.array([1000,1000]) # number of training examples
norm_SF_ = True              # normalize structure functions before fit
norm_plane_ = True           # normalize plane s.t. std(S) = 1

# Opens files for input and output
rs.OpenSFI(name_rSoftSF)
rs.OpenDynamicsI(name_MD, name_Dynamics)
rs.OpenPlaneO(name_plane)

# Selects training set from arrays
rs.SelectTrainingSet(
      rearrangement_cutoff=r_cut,
      non_rearrangement_frames=nr_frames,
      non_rearrangement_cutoff=nr_cut)

# Prints the maximum number of training examples in rearranging
# and non-rearranging training sets
print('Number of examples for each type in rearranging set')
print([len(tR) for tR in rs.training_R])
print('Number of examples for each type for non-rearranging set')
print([len(tNR) for tNR in rs.training_NR])

# Trains plane
rs.Train(
      #n_eg = n_train,
      norm_SF = norm_SF_,
      norm_plane = norm_plane_)

# Writes plane to file
rs.WritePlane()

# Closes all files
rs.CloseSFI()
rs.CloseDynamicsI()
rs.ClosePlaneO()
