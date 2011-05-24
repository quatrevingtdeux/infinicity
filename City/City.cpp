
#include <iterator>
#include <ctime>

#include "City.h"
#include "../Geom/Vertex.h"

City::City()
{
	// here for personnalisation variables
	size = 40.0f;
	humanSize = 1.0f; // 2 mètres
}

City::City(double size, double humanSize) : size(size), humanSize(humanSize)
{}

City::~City()
{}

void City::Generate()
{
	// Generate Frontiers
	frontiers.push_back(new Vertex(-size/2.f, -size/2.f, 0.f));
	frontiers.push_back(new Vertex( size/2.f, -size/2.f, 0.f));
	frontiers.push_back(new Vertex( size/2.f,  size/2.f, 0.f));
	frontiers.push_back(new Vertex(-size/2.f,  size/2.f, 0.f));
	
	// Generate Area	
	for (int i = 0; i < 4; ++i)
	{
		areas.push_back(new Area());
	}
	
	for (std::vector<Area*>::iterator it = areas.begin();
		it != areas.end(); ++it)
	{
		(*it)->Subdivide();
	}
}