#ifndef AREA_H
#define AREA_H

#include <vector>
#include "Block.h"
#include "../Geom/Vertex.h"

class Area
{
	public:
		Area();
		Area(std::vector<Vertex*>* frontiers);
		~Area();
		
		void Subdivide();

		std::vector<Block*> &GetBlocks() const { return *blocks; }
	private:
		void CreateSquareBlocks(int number);
		
		std::vector<Block*>* blocks;
		std::vector<Vertex*>* vertices; // frontiers
};

#endif
