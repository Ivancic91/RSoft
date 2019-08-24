import numpy as np
from RSoftTools import RSoft


# Defines radial SF parameters
dL = 0.05
etol_rad = 0.01
mus = np.arange(0.9,1.41,dL)
n_SF_rad = len(mus)
Ls = np.ones(n_SF_rad)*dL
radial_Xs = np.ones(n_SF_rad)
radial_Ys = np.ones(n_SF_rad)

# Defines angular SF parameters
# etol_ang = 0.05
# xis = np.array([1.75,1.75,1.75,1.75,1.20,1.20,2.00,2.00,2.00,2.00])
# lambdas = np.array([1, 1, 1, 1, 1, 1,-1,-1,-1,-1])
# zetas = np.array([1,2,4,16,1,2,1,2,4,16])
# n_SF_ang = len(xis)
# angular_Xs = np.ones(n_SF_ang)
# angular_Ys = np.ones(n_SF_ang)
# angular_Zs = np.ones(n_SF_ang)

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
