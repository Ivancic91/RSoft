#include "VectorTools.hpp"
#include <vector>
#include <math.h>

int VectorTools::BinValueSortedVec(std::vector<double>& vec, double val)
{
  bool found_bin = false;
  int idx_max, idx_min, idx_bin;
  double val_diff, bin_diff, bin_val;
  idx_max = vec.size()-1;
  idx_min = 0;

  if(val < vec[idx_min]+(vec[idx_min+1]-vec[idx_min])/2.)
  {
    idx_bin = 0;
  }
  else if(val > vec[idx_max]-(vec[idx_max]-vec[idx_max-1])/2.)
  {
    idx_bin = vec.size();
  }
  else
  {
    while(!found_bin)
    {
      idx_bin = (idx_max+idx_min)/2;
      bin_val = vec[idx_bin];
      if(bin_val<val)
      {
        val_diff = val-vec[idx_bin];
    	bin_diff = vec[idx_bin+1]-bin_val;
        if(fabs(val_diff) < fabs(bin_diff)/2.)
    	{
          found_bin = true;
        }
        else
        {
          idx_min = idx_bin;
        }
      }
      else
      {
        val_diff = val-vec[idx_bin];
        bin_diff = vec[idx_bin-1]-bin_val;
        if(fabs(val_diff) < fabs(bin_diff)/2.)
    	{
          found_bin = true;
        }
        else
        {
          idx_max = idx_bin;
        }
      }
    }
  }



  return idx_bin;
}
