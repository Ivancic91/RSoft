#include "VectorTools.hpp"
#include <vector>

double VectorTools::MinCol(std::vector<std::vector<double> >& vec, int col)
{
	double min;
	min = vec[0][col];
	for(int ii=0; ii<vec.size(); ii++)
	{
		if(min>vec[ii][col])
		{
			min = vec[ii][col];
		}
	}

	return min;
}
