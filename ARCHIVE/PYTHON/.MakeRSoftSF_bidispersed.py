import numpy as np
from RSoftTools import RSoft


# Defines radial SF parameters
dL = 0.05
etol_rad = 0.01
mus_11 = np.arange(0.95,1.4,dL)
n_SF_rad_11 = len(mus_11)
radial_Xs_11 = np.ones(n_SF_rad_11)
radial_Ys_11 = np.ones(n_SF_rad_11)
mus_12 = np.arange(0.8,1.4,dL)
n_SF_rad_12 = len(mus_12)
radial_Xs_12 = np.ones(n_SF_rad_12)
radial_Ys_12 = 2*np.ones(n_SF_rad_12)
mus_21 = np.arange(0.8,1.4,dL)
n_SF_rad_21 = len(mus_21)
radial_Xs_21 = 2*np.ones(n_SF_rad_21)
radial_Ys_21 = np.ones(n_SF_rad_21)
mus_22 = np.arange(0.9,1.4,dL)
n_SF_rad_22 = len(mus_22)
radial_Xs_22 = 2*np.ones(n_SF_rad_22)
radial_Ys_22 = 2*np.ones(n_SF_rad_22)
mus = np.concatenate((mus_11,mus_12,mus_21,mus_22))
Ls = np.ones(n_SF_rad_11+n_SF_rad_12+n_SF_rad_21+n_SF_rad_22)*dL
radial_Xs = np.concatenate((radial_Xs_11, radial_Xs_12, radial_Xs_21, \
      radial_Xs_22))
radial_Ys = np.concatenate((radial_Ys_11, radial_Ys_12, radial_Ys_21, \
      radial_Ys_22))


# Defines angular SF parameters
#etol_ang = 0.05
#xis = np.array([1.75,1.75,1.75,1.75,1.20,1.20,2.00,2.00,2.00,2.00])
#lambdas = np.array([1, 1, 1, 1, 1, 1,-1,-1,-1,-1])
#zetas = np.array([1,2,4,16,1,2,1,2,4,16])
#n_SF_ang = len(xis)
#angular_Xs = np.ones(n_SF_ang)
#angular_Ys = np.ones(n_SF_ang)
#angular_Zs = np.ones(n_SF_ang)


rs = RSoft()
rs.OpenSFO('SF.nc')
rs.SetRSoftSF(\
      etol_rad = etol_rad,\
      mus = mus, \
      Ls = Ls, \
      radial_Xs = radial_Xs, \
      radial_Ys = radial_Ys)#, \
#      etol_ang = etol_ang, \
#      xis = xis, \
#      lambdas = lambdas, \
#      zetas = zetas, \
#      angular_Xs = angular_Xs, \
#      angular_Ys = angular_Ys, \
#      angular_Zs = angular_Zs)
rs.CloseSFO()
