#ifndef DENSITYMAP_H
#define DENSITYMAP_H

#include <fstream>
#include <string>
#include "../Geom/Vertex.h"

class DensityMap
{
	public:
		DensityMap();
		DensityMap(std::string filename);
		~DensityMap();

		double Density(double x, double y);
		double Density(Vertex &v);
	private:
		std::ifstream file;
		std::string filename;
};

#endif
