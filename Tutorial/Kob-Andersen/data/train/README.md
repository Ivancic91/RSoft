This directory contains the data and the LAMMPs input scripts for the 
Kob-Andersen tutorial of RSoft. For real projects keeping input scripts
and originally generated data is a good practice so parameters that 
were used are not lost. Here are descriptors of the files:

input.therm : LAMMPS input script to thermalize an 80-20 Kob-Andersen
      mix at a large particle density of 0.96
input.lowerT : LAMMPS input script to lower the temperature of the mix
      from T=1.0 to T=0.47 at a cooling rate of 10^(-4). The simulation
      is run 10 alpha-relaxation times at T=0.47 to relax it.
input.run : LAMMPS input script to run trajectory for softness training
ss_run : slurm submission script to request 12 processors to run LAMMPS
      input scripts in series
