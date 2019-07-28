#include "VectorTools.hpp"
#include <vector>
#include <iostream>

void VectorTools::Clear2DVec(std::vector<std::vector<double> >& vec)
{
  for(int n=0; n<vec.size(); n++)
  {
    vec[n].clear();
  }
  vec.clear();
}
void VectorTools::Clear2DVec(std::vector<std::vector<int> >& vec)
{
  for(int n=0; n<vec.size(); n++)
  {
    vec[n].clear();
  }
  vec.clear();
  //std::vector< std::vector<int> > tmp;
  //vec = tmp;
}
