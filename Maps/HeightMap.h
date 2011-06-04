#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <fstream>
#include <string>
#include "../Geom/Vertex.h"

class HeightMap
{
	public:
		HeightMap();
		HeightMap(std::string filename);
		~HeightMap();

		void Z(double x, double y);
		void Z(Vertex &v);
	private:
		std::ifstream file;
		std::string filename;
};

#endif
