#include "VectorTools.hpp"
#include <vector>

double VectorTools::MaxCol(std::vector<std::vector<double> >& vec, int col)
{
	double max;
	max = vec[0][col];
	for(int ii=0; ii<vec.size(); ii++)
	{
		if(max<vec[ii][col])
		{
			max = vec[ii][col];
		}
	}

	return max;
}
