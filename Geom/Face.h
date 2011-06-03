#ifndef FACE_H
#define FACE_H

#include <vector>
#include "Vertex.h"

class Face
{
	public:
		Face();
		Face(std::vector<Vertex*>* v) : vertices(v) {}
		~Face();
		
		void Translate(double x, double y, double z);
		
		std::vector<Vertex*> &GetVertices() { return *vertices; }
		int GetVerticesNumber() { return vertices->size(); }
	private:
		std::vector<Vertex*>* vertices;
};

#endif