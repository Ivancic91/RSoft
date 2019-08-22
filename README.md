# RSoft 1.0

The following document is an introduction to the RSoft project. This 
project is meant to be a sharable softness code with slight 
modifications to structure functions listed in Cubuk et. al. PRL 2015.

Original code was written by Robert Ivancic. Please feel free to email
ivancic91 [at] gmail [dot] com. Publications with this code are
forthcoming.

## Structure function definitions

The structure functions currently calculated in this code come in two 
types:

<a href="https://www.codecogs.com/eqnedit.php?latex=G_{\text{R}}(i;&space;\mu,&space;L,&space;X,&space;Y)&space;=&space;\sum_j&space;\text{max}\left(e^{-(R_{ij}-\mu)^2/L^2}-\epsilon_{\text{R}},&space;0\right)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?G_{\text{R}}(i;&space;\mu,&space;L,&space;X,&space;Y)&space;=&space;\sum_j&space;\text{max}\left(e^{-(R_{ij}-\mu)^2/L^2}-\epsilon_{\text{R}},&space;0\right)" title="G_{\text{R}}(i; \mu, L, X, Y) = \sum_j \text{max}\left(e^{-(R_{ij}-\mu)^2/L^2}-\epsilon_{\text{R}}, 0\right)" /></a>

<a href="https://www.codecogs.com/eqnedit.php?latex=G_{\text{A}}(i;&space;\xi,&space;\lambda,&space;\zeta,&space;X,&space;Y,&space;Z)&space;=&space;\sum_{j,k}&space;\text{max}\left(e^{-(R_{ij}^2&plus;R_{jk}^2&plus;R_{ik}^2)/\xi^2}\left(\frac{1&plus;\lambda}{2}\right)^\zeta-\epsilon_{\text{A}},&space;0\right)" target="_blank"><img src="https://latex.codecogs.com/gif.latex?G_{\text{A}}(i;&space;\xi,&space;\lambda,&space;\zeta,&space;X,&space;Y,&space;Z)&space;=&space;\sum_{j,k}&space;\text{max}\left(e^{-(R_{ij}^2&plus;R_{jk}^2&plus;R_{ik}^2)/\xi^2}\left(\frac{1&plus;\lambda}{2}\right)^\zeta-\epsilon_{\text{A}},&space;0\right)" title="G_{\text{A}}(i; \xi, \lambda, \zeta, X, Y, Z) = \sum_{j,k} \text{max}\left(e^{-(R_{ij}^2+R_{jk}^2+R_{ik}^2)/\xi^2}\left(\frac{1+\lambda}{2}\right)^\zeta-\epsilon_{\text{A}}, 0\right)" /></a>

where most constants are defined in Cubuk et. al. PRL 2015 and <a href="https://www.codecogs.com/eqnedit.php?latex=\epsilon_i" target="_blank"><img src="https://latex.codecogs.com/gif.latex?\epsilon_i" title="\epsilon_i" /></a> are the error tolerances for the radial (R) and angular (A) structure functions. These values should fall between 0 and 1; typically I have choosen 0.01 or 0.05. This formulation is used for two reasons. First, structure functions are smooth allowing for better interpretation of softness as an energy barrier for rearrangement (Schoenholz et. al. Nat. Phys. 2016). Second, it prevents unreasonable choices of parameters by the user.

## Installation

Here, we assume that installed you have (a) python 3 (b) anaconda, and
(c) git on your system.

**(Step 1)** Go to your home directory and clone this repository. This
can be done through the commands:

```bash
cd ~
git clone https://github.com/Ivancic91/RSoft
``` 

**(Step 2)** Create a conda environment. This will ensure that you can use
the packages you need without interfering with existing packages. You
may do this from the yml environment in the RSoft directory.

```bash
cd ~/RSoft
conda env create -f RSoft.yml
```

Make sure installation completed correctly by reading the conda output. 
To activate/deactive the RSoft environment, use the commands:

```bash
conda activate RSoft # For MacOS, use `source activate RSoft`
conda deactivate
```

**(Step 3)** Link c++ libraries, include the c++ headers, and add 
~/RSoft/RSoftPython to your PYTHONPATH. To do this, you can run:

```bash
cd ~/RSoft
python setup.py
source ~/.bashrc
```

Congratulations! You have installed RSoft.

## Tutorial

### Kob-Andersen

The following is a tutorial on how to develop a softness field for a
3D Kob-Andersen 80-20 mixture. 

**(Step 1)** Get data and convert it to an AMBER format. 

We have already run a LAMMPs simulation of this system with 1000 
particles for approximately 1 alpha relaxation time for you. Details
about the simulation can be found in the data directory of the
Kob-Andersen tutorial. For now, we are simply going to grab the 
trajectory and use it.

```bash
cd ~/RSoft/Tutorial/Kob-Andersen/
cp data/run.lammpstrj work/train.lammpstrj
```

Next, we will now copy a script to convert our trajectory to a AMBER 
(netCDF) file. Note that this script is written only for a Kob-Andersen
simulation for other types of simulations and experiments this script
may need to be modified. More information about the functions used in
this script may be found: https://ivancic91.github.io/LammpsIO/.

```bash
cp ~/RSoft/ARCHIVE/PYTHON/ConvDumpToNc_KA.py work
conda activate RSoft
cd work
python ConvDumpToNc_KA.py train.lammpstrj train.nc
``` 

It is important to note that AMBER style trajectories assume a 
*constant* number of particles in each frame. This assumption is not
limiting however because we can add *NaN* as the x, y, and z coordinate
of any particle which is not in the frame. Even though there are a 
constant number of particles in the simulation, the script used above
performs this operation and can be used as a template for experiments
and simulations with differing numbers of particles.

To check that the conversion completed correctly you may use the 
ncdump command which will print the contents of train.nc to the 
terminal.

```bash
ncdump train.nc
conda deactivate
```

**(Step 2)** Evaluate a dynamic quantity for each particle and frame.

The traditional dynamic quantities used in softness development are 
<a href="https://www.codecogs.com/eqnedit.php?latex=D^2_{min}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?D^2_{min}" title="D^2_{min}" /></a>
in mechanically strained systems and <a href="https://www.codecogs.com/eqnedit.php?latex=p_{hop}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p_{hop}" title="p_{hop}" /></a>
in quiescent systems. More information about both of these quantities
can be found in [Falk and Langer, Phy. Rev. E (1998)] and 
[Smessaert and Rottler, Phys. Rev. E (2013)] respectively. Because we
are not straining our Kob-Andersen glass we will simply use 
<a href="https://www.codecogs.com/eqnedit.php?latex=p_{hop}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p_{hop}" title="p_{hop}" /></a>
for this analysis.

To do this, we are going to use some pre-written C++ code from the code
archive. This code is well-commented and may be modified if necessary.

```bash
cd ~/RSoft
cp ARCHIVE/STANDARD_ANALYSIS/CalcPhop.cpp RSoft_MAIN.cpp
```

We now will make an executable from RSoft_MAIN.cpp and move it to the 
work directory.

```bash
cd Debug
make all
mv RSoft.exe ~/RSoft/Tutorial/Kob-Andersen/work/Phop.exe
``` 

Finally, we will evaluate <a href="https://www.codecogs.com/eqnedit.php?latex=p_{hop}" target="_blank"><img src="https://latex.codecogs.com/gif.latex?p_{hop}" title="p_{hop}" /></a>
for every particle at every frame of the training set. This function 
will cut off a few frames at the beginning and end of the trajectory
due to the rearrangement time [tR]. Note that basic usage for this 
executable can be found by executing the function with no arguments 
as shown below and detailed usage is shown in the C++ code comments. 

```bash
cd ~/RSoft/Tutorial/Kob-Andersen/work/
./Phop.exe
./Phop.exe train.nc 10 p p p phop.nc
```

The above code will take around 5 minutes to run. The parameter tR = 10
was taken from Schoenholz et. al. Nat. Phys. 2016.

**(Step 3)** Generate an RSoftSF file with particles evaluated.

In order to evalutate structure functions for a set of particles, we 
need to define the parameter sets over which to evaluate them. To do
this, 

**(Step 4)** Traditional approach to training.


## FAQs

- **How do I determine what a "rearrangement" is?**

- **How do I determine which structure functions to use?**

- **Why is my softness calculation so slow?**

## Documentation

- **RSoftTools** : This is a set of python code used extensively to perform the less computationally intensive parts of the softness calculates. Documentation is available here: https://ivancic91.github.io/RSoft/

- **LammpsIO** : This is a set of python code that was re-written in C++ for this project. It allows for quickly inputing and outputing LAMMPS style dump and AMBER files. It is provided during the installation of RSoft. Complete documentationis provided here: https://ivancic91.github.io/LammpsIO/

- **AMBER** : A file format based on netCDF that was developed for storing data generated by molecular dynamics simulations. More information about this format is available here: http://ambermd.org/netcdf/nctraj.xhtml

## Publications
