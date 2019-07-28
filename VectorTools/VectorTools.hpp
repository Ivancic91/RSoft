/*
 * VectorTools.hpp
 *
 *  Created on: Oct 17, 2016
 *      Author: Robert
 */

#ifndef VECTORTOOLS_HPP_
#define VECTORTOOLS_HPP_

#include <vector>
#include "../Eigen/Dense"

class VectorTools
{
private:


public:

  // 1D
  int BinValueSortedVec(std::vector<double>& vec, double bin_val);
  double Mean1D(std::vector<double>& vec);
  double Std1D(std::vector<double>& vec);
  void Multiply1D(double scalar, std::vector<double>& vec);

  // 2D
  void Clear2DVec(std::vector<std::vector<double> >& vec);
  void Clear2DVec(std::vector<std::vector<int> >& vec);
  void Vec2DToEigenMat(
    std::vector<std::vector<double> >& vec,
    Eigen::MatrixXd& mat);
  void EigenMatToVec2D(
    Eigen::MatrixXd& mat,
    std::vector<std::vector<double> >& vec);
  double MaxCol(std::vector<std::vector<double> >& vec, int col);
  double MinCol(std::vector<std::vector<double> >& vec, int col);


};


#endif /* VECTORTOOLS_HPP_ */
