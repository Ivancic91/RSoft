#include "VectorTools.hpp"
#include <vector>
#include <numeric>

void VectorTools::Multiply1D(double scalar, std::vector<double>& vec)
{
  std::transform(vec.begin(), vec.end(), vec.begin(),
    std::bind1st(std::multiplies<double>(), scalar));
}
