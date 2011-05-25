#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Vertex.h"

class Face
{
	public:
		Face();
		//Face(Vertex* tL, Vertex* bR) : topLeft(tL), bottomRight(bR) {}
		Face(std::vector<Vertex*>* v) : vertices(v) {}
		~Face();
		
		std::vector<Vertex*> &GetVertices() { return *vertices; }
	private:
		std::vector<Vertex*>* vertices;
		//Vertex* topLeft;
		//Vertex* bottomRight;
};

#endif