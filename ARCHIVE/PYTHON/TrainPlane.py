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

start = time.time()
# Opens files for input and output
name_rSoftSF = '/opt/share/entaoy/Phop_SF/out.SF.nc'
name_MD = 'Phop_tmp.nc'
name_Dynamics = 'phop'
name_plane = 'out.plane.nc'
r_cut = np.array([0.2])      # phop cutoff for rearrangements (r's)
nr_frames = np.array([10])   # number of frames below non-r threshold
nr_cut = np.array([0.05])    # non-r threshold
n_train = 5000               # number of rearrangingtraining examples
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

# Trains plane
rs.Train(
      n_eg = np.array([n_train]),
      norm_SF = norm_SF_,
      norm_plane = norm_plane_)

# Writes plane to file
rs.WritePlane()

# Closes all files
rs.CloseSFI()
rs.CloseDynamicsI()
rs.ClosePlaneO()
end = time.time()
print((end-start))
