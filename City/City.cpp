
#include <ctime>

#include "City.h"
#include "../Geom/Vertex.h"

City::City()
{
	// here for personnalisation variables
}

City::City(double size, double humanSize) : size(size), humanSize(humanSize)
{}

City::~City()
{}

void City::Generate()
{
	for (int i = 0; i < 4; ++i)
	{
		areas.push_back(new Area());
	}
}