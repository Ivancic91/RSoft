"""


"""
from LammpsIO import DumpIO
from LammpsIO import NetCDFIO
import numpy as np
import sys

script, in_dump, out_nc = sys.argv

# Opens DumpIO and NetCDFIO objects import and export trajectories
dump = DumpIO()
dump.OpenI(in_dump)
nc = NetCDFIO()
nc.OpenO(out_nc)

# Gets number of frames from input file
n_f = dump.NumFrames()

# Gets numpy array of all unique particle ids and finds total number of
# unique particles, n_p, and dimension of space, d
ids = np.array([])
for f in range(n_f):
  dump.LoadNextFrame()
  id_t = dump.GetID()
  ids = np.append(ids, id_t)
ids = np.sort(np.unique(ids))
n_p = len(ids)
d = dump.GetPos().shape[1] 
dump.CloseI()

# Creates a dictionary so that one inputs particle id and the id's 
# position in the array in output
id_to_idx = dict([(id_,idx) for idx, id_ in enumerate(ids)])

# Reopens DumpIO object for import
dump = DumpIO()
dump.OpenI(in_dump)

for f in range(n_f):

  # Prints frame every 50 frames
  if f%50==0:
    print(f)

  # Reads all data from dump file
  # NOTE: All trajectories that interact with RSoft should have a
  #       "type" data column which gives an integer type label to
  #       each particle. If your system only has a single type of
  #       particle and the dump file has no type data column, then
  #       you may comment out the line beginning with type_t and 
  #       uncomment the line below that.
  dump.LoadNextFrame()
  t = dump.Gett()
  bb_t = dump.GetBB()
  id_t = dump.GetID()
  pos_t = dump.GetPos()
  type_t = dump.GetDataCol('type')
  # type_t = np.ones(len(id_t))

  # Finds indices of particles 
  idx_t = np.array([id_to_idx[id_] for id_ in id_t])

  # Creates NaN arrays for all data arrays
  type_write_t = np.empty(n_p)
  type_write_t[:] = np.nan
  pos_write_t = np.empty((n_p, d))
  pos_write_t[:] = np.nan

  # Fills arrays with data
  type_write_t[idx_t] = type_t
  pos_write_t[idx_t] = pos_t

  # Saves data in AMBER format, note that no id's are saved because
  # particles are assumed to be in order.
  nc.Sett(f,t)
  nc.SetBB(f, bb_t)
  nc.SetPos(f, pos_write_t)
  nc.SetDataCol(f, 'type', type_write_t)

dump.CloseI()
nc.CloseO()







