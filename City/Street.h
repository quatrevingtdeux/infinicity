#ifndef STREET_H
#define STREET_H

#include "../Geom/Vertex.h"
#include "../Geom/Face.h"

class Street
{
	public:
		Street();
		~Street();
		
		std::vector<Face*> &GetFaces() const { return *faces; }
	private:
		Vertex begin;
		Vertex end;
		double width;
		std::vector<Face*>* faces;
};

#endif