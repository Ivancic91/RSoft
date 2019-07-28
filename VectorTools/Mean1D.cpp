#include "VectorTools.hpp"
#include <vector>
#include <numeric>

double VectorTools::Mean1D(std::vector<double>& vec)
{
  double sum = std::accumulate(vec.begin(), vec.end(), 0.0);
  double mean = sum / ((double) vec.size());

  return mean;
}
