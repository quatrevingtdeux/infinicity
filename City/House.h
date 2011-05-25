#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include "../Geom/Vertex.h"

class House
{
	public:
		House();
		House(std::vector<Vertex*>* frontiers) : vertices(frontiers) {}
		~House();
		
		void Build();
	private:
		std::vector<Vertex*>* vertices;
};

#endif