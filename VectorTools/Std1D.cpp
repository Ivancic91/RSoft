#include "VectorTools.hpp"
#include <vector>
#include <numeric>

double VectorTools::Std1D(std::vector<double>& vec)
{
  double mean = Mean1D(vec);
  std::vector<double> diff(vec.size());
  std::transform(vec.begin(), vec.end(), diff.begin(),
    std::bind2nd(std::minus<double>(), mean));
  double sq_sum = std::inner_product(diff.begin(), diff.end(), diff.begin(), 0.0);
  double stdev = std::sqrt(sq_sum/((double) vec.size()));

  return stdev;


}
