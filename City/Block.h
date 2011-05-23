#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "../Geom/Vertex.h"

class Block
{
	public:
		Block();
		~Block();

	private:
		std::vector<Vertex*> vertices; // frontiers

};

#endif
