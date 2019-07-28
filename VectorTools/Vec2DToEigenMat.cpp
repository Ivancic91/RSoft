#include "VectorTools.hpp"
#include <vector>
#include <iostream>

void VectorTools::Vec2DToEigenMat(
		std::vector<std::vector<double> >& vec,
		Eigen::MatrixXd& mat)
{
	std::vector<double> temp;
	int n_rows, n_cols;

	temp = vec[0];
	n_rows = vec.size();
	n_cols  = temp.size();
	mat.resize(0,0);
	mat.resize(n_rows,n_cols);

	for(int row=0; row<n_rows; row++)
	{
		for(int col=0; col<n_cols; col++)
		{
			mat(row,col) = vec[row][col];
		}
	}

}
