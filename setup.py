import sys
import os

anaconda_dir = 'anaconda3'
debug_dir = 'Debug'
conda_env = 'RSoft1'


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
str_netcdf = str_anaconda+'envs/'+conda_env
for dname, dirs, files in os.walk(debug_dir):
  for fname in files:
    if fname == 'makefile' or fname[-3:] == '.mk':
      fpath = os.path.join(dname, fname)
      print(fpath)
      with open(fpath) as f:
        s = f.read()
      s = s.replace("$(NETCDFHOME)", str_netcdf)
      with open(fpath, "w") as f:
        f.write(s)



