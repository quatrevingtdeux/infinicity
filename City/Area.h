#ifndef AREA_H
#define AREA_H

#include <vector>
#include "Block.h"
#include "../Geom/Vertex.h"
#include "../Geom/GeomOp.h"

class Area
{
	public:
		Area();
		Area(std::vector<Vertex*>* frontiers);
		~Area();
		
		void Subdivide();
		
		double GetSurface() const { return Surface(*vertices); }
		std::vector<Vertex*> &GetVertices() { return *vertices; }
		std::vector<Block*> &GetBlocks() const { return *blocks; }
	private:
		void CreateSquareBlocks(std::vector<Vertex *> &vertices);
		void CreateTriangleBlocks(std::vector<Vertex *> &vertices);
		
		std::vector<Block*>* blocks;
		std::vector<Vertex*>* vertices; // frontiers
};

#endif
