#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include "../Geom/Vertex.h"

class House
{
	public:
		House();
		~House();

	private:
		std::vector<Vertex*> vertices;
};

#endif