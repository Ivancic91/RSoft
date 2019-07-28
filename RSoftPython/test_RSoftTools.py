from RSoftTools import RSoft
import random
import numpy as np
from LammpsIO import NetCDFIO

# Initializes RSoft object
rs = RSoft()

# Opens files for input and output
name_rSoftSF = '/opt/share/entaoy/Phop_SF/out.SF.nc'
name_MD = 'Phop_tmp.nc'
name_Dynamics = 'phop'
name_plane = 'out.plane.nc'
rs.OpenSFI(name_rSoftSF)
rs.OpenDynamicsI(name_MD, name_Dynamics)
rs.OpenPlaneO(name_plane)

# Causes RSoft to only consider first 200 frames. This line is 
# added for testing purposes and should be comented out during real
# use.
rs._n_f = 200

# Selects training set from arrays
r_cut = np.array([0.2])      # phop cutoff for rearrangements (r's)
nr_frames = np.array([10])   # number of frames below non-r threshold
nr_cut = np.array([0.05])    # non-r threshold
rs.SelectTrainingSet(\
      rearrangement_cutoff=r_cut,
      non_rearrangement_frames=nr_frames,
      non_rearrangement_cutoff=nr_cut)

# Preliminary tests
print 'TESTS OF TRAINING SET SELECTION'
print '-------------------------------'
print 'I. BASIC TESTS'
rearranging_training_set = rs.training_R[0]
non_rearranging_training_set = rs.training_NR[0]
n_R = len(rearranging_training_set)
n_NR = len(non_rearranging_training_set)
print 'Number of rearranging examples = ' + str(n_R)
print '      NOTE: This should decrease with increasing r_cut'
print 'Number of non-rearranging examples = ' + str(n_NR)
print '      NOTE: This should decrease with decreasing nr_cut and'
print '      increasing nr_frames'
print ' '

print 'II. CHECK DYNAMICS OF RANDOM SAMPLE'
nc = NetCDFIO()
nc.OpenI(name_MD)
n_random = 100   # Number of random particles to check
rand_R = np.random.randint(0,high=n_R,size=n_random)
rand_NR = np.random.randint(0,high=n_NR,size=n_random)
ta = int(nr_frames[0] / 2)
for ii in range(n_random):
  f_R = rearranging_training_set[rand_R[ii]][0]
  p_R = rearranging_training_set[rand_R[ii]][1]
  phop_R = nc.GetDataCol(f_R, name_Dynamics)[p_R]
  if phop_R > r_cut[0]:
    print 'rearrangement worked: phop = ' + str(phop_R)
  else:
    print '      ERROR: rearrangement did not work: phop = ' + str(phop_R)
    print '            f_R = ' + str(f_R) + ', p_R = ' + str(p_R)

  worked_NR = True
  f_NR = non_rearranging_training_set[rand_NR[ii]][0]
  p_NR = non_rearranging_training_set[rand_NR[ii]][1]
  arr = []
  for dt in range(-ta, ta+1):
    phop_NR_tmp = nc.GetDataCol(f_NR+dt, name_Dynamics)[p_NR]
    arr.append(phop_NR_tmp)
    if phop_NR_tmp > nr_cut[0]:
      worked_NR = False
  if worked_NR:
    print 'non-rearrangement worked: phop = ' + str(phop_NR_tmp)
  else:
    print '      ERROR: non-rearrangement did not work: phop = '
    print arr
    print '            f_NR = ' + str(f_NR) + ', p_R = ' + str(p_NR)
nc.CloseI()
print ' '

print 'II. CHECK STRUCTURES OF RANDOM SAMPLE'
n_random = 1000
rand_R = np.random.randint(0,high=n_R,size=n_random)
rand_NR = np.random.randint(0,high=n_NR,size=n_random) 
SFs_R = np.mean(rs._ParticlesToSFs(rearranging_training_set[rand_R]),axis=0)[:-10]
SFs_NR = np.mean(rs._ParticlesToSFs(non_rearranging_training_set[rand_NR]),axis=0)[:-10]
SFs_R = SFs_R / np.sqrt(2.0*np.pi*0.1**2)/(rs.mus)**2
SFs_NR = SFs_NR / np.sqrt(2.0*np.pi*0.1**2)/(rs.mus)**2
mus = rs.mus
np.savetxt('grs.dat',np.array([mus,SFs_R,SFs_NR]).T)
print ' '
print ' '
print ' '

print 'TESTS OF TRAINING'
print '-----------------'
print 'I. TEST ACCURACY'
n_train = 5000
rs.Train(
      n_eg = np.array([n_train]),   # num training examples to use
      norm_SF = True,               # normalize structure functions
      norm_plane = True             # normalize softness to 1
)
SFs_R = rs._ParticlesToSFs(rearranging_training_set[rand_R])
SFs_NR = rs._ParticlesToSFs(non_rearranging_training_set[rand_NR])
plane = np.hstack((rs.radial_plane, rs.angular_plane))
print '      rearranging test set accuracy = '
print len(np.where(np.dot(plane,SFs_R.T)+rs.intercept > 0)[1]) / float(n_random)
print '      non-rearranging test set accuracy = '
print len(np.where(np.dot(plane,SFs_NR.T)+rs.intercept < 0)[1]) / float(n_random)
sr = np.dot(rs.radial_plane,rs.GetRadial(0).T)
sa = np.dot(rs.angular_plane,rs.GetAngular(0).T)
s = sr + sa + rs.intercept
wCOVw = np.dot(np.dot(plane[0],rs._cov_SF),plane[0])
print '      soft mean = ' + str(np.mean(s))
print '      soft std = ' + str(np.std(s))
print '      w.cov_SF.w = ' + str(wCOVw)

print 'II. WRITE PLANE'
rs.WritePlane()

# Closes all files
rs.CloseSFI()
rs.CloseDynamicsI()
rs.ClosePlaneO()
