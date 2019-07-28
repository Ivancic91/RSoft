#include "VectorTools.hpp"
#include <vector>
#include <iostream>

void VectorTools::EigenMatToVec2D(
		Eigen::MatrixXd& mat,
		std::vector<std::vector<double> >& vec)
{
	int n_rows, n_cols;
	std::vector<double> temp;
    VectorTools vtool;

    vtool.Clear2DVec(vec);
	n_rows = mat.rows();
	n_cols = mat.cols();

	for(int row=0; row<n_rows; row++)
	{
		temp.clear();
		for(int col=0; col<n_cols; col++)
		{
			temp.push_back(mat(row,col));
		}
		vec.push_back(temp);
	}

}
