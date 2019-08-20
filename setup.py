import sys
import os
import numpy as np
import shutil

anaconda_dir = 'anaconda3'
debug_dir = 'Debug/'
conda_env = 'RSoft'


# Finds where the anaconda directory is:
path = sys.path
idx = 0
found_dir = False
found_anaconda = False
while not found_dir:
  found_dir = ('/'+anaconda_dir+'/' in path[idx])
  idx += 1
anaconda_arr = path[idx].split('/')
idx = 0
while not found_anaconda:
  found_anaconda = (anaconda_arr[idx] == anaconda_dir)
  idx += 1
str_anaconda = '/'.join(anaconda_arr[:idx])
print('Your anaconda directory is located: '+str_anaconda)

# replaces $(NETCDFHOME) with str_netcdf in Debug directory 
str_netcdf = str_anaconda+'/envs/'+conda_env
try:
  shutil.rmtree(debug_dir)
  shutil.copytree('.Debug', debug_dir)
except:
  shutil.copytree('.Debug', debug_dir)
for dname, dirs, files in os.walk(debug_dir):
  for fname in files:
    if fname == 'makefile' or fname[-3:] == '.mk':
      fpath = os.path.join(dname, fname)
      with open(fpath) as f:
        s = f.read()
      s = s.replace("$(NETCDFHOME)", str_netcdf)
      with open(fpath, "w") as f:
        f.write(s)

# Adds RSoftPython to the python path and sources .bashrc
rsoft_dir = path[0]+'/RSoftPython/'
f=open(os.path.expanduser('~')+'/.bashrc')
lines = f.readlines()
f.close()
if '# Added by RSoft setup.py\n' not in lines:
  print('Appending to .bashrc PYTHONPATH modification')
  f=open(os.path.expanduser('~')+'/.bashrc', 'a+')
  f.write('\n# Added by RSoft setup.py\n')
  f.write('export PYTHONPATH="${PYTHONPATH}:'+rsoft_dir+'"')
  f.close()
  
else:
  print('Modifying .bashrc PYTHONPATH modification')
  idx = np.where('# Added by RSoft setup.py\n' == np.array(lines))[0][0]
  lines[idx+1] = 'export PYTHONPATH="${PYTHONPATH}:'+rsoft_dir+'"'
  f=open(os.path.expanduser('~')+'/.bashrc', 'w')
  f.writelines(lines)
  f.close()
