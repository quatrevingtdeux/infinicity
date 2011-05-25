#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include "../Geom/Vertex.h"
#include "../Geom/Face.h"

class House
{
	public:
		House();
		House(std::vector<Vertex*>* frontiers) : vertices(frontiers) {}
		~House();
		
		void Build();
		
		std::vector<Face*> &GetFaces() { return *faces;}
	private:
		std::vector<Vertex*>* vertices;
		std::vector<Face*>* faces;
};

#endif