#include "MDTools.hpp"
#include <math.h>

void MDTools::CalculateTheta(
		std::vector< std::vector<double> >& pos,
		std::vector<double>& theta)
{
	theta.clear();
	n_p = pos.size();
	double x, y;

	for(int p=0; p<n_p; p++)
	{
		x = pos[p][0];
		y = pos[p][1];

		theta.push_back(atan2(y,x));
	}
}
