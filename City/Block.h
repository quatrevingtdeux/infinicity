#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "../Geom/Vertex.h"
#include "House.h"

class Block
{
	public:
		Block();
		Block(std::vector<Vertex*>* frontiers) : vertices(frontiers) {}
		~Block();
		
		void Generate() {}
		
	private:
		std::vector<House*> houses;
		std::vector<Vertex*>* vertices; // frontiers

};

#endif
