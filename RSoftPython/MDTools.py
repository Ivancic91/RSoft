import numpy as np
import sys


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

