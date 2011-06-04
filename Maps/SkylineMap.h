#ifndef SKYLINEMAP_H
#define SKYLINEMAP_H

#include <fstream>
#include <string>
#include "../Geom/Vertex.h"

class SkylineMap
{
	public:
		SkylineMap();
		SkylineMap(std::string filename);
		~SkylineMap();

		double GetMaxHeight(double x, double y);
		double GetMaxHeight(Vertex &v);
	private:
		std::ifstream file;
		std::string filename;
};

#endif
