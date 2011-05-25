#ifndef STREET_H
#define STREET_H

#include "../Geom/Vertex.h"
#include "../Geom/Face.h"

class Street
{
	public:
		Street();
		~Street();
		
		void Build();
		
		std::vector<Face*> &GetFaces() const { return *faces; }
	private:
		void CreatePlaneStreet();
		
		std::vector<Vertex*>* vertices;
		std::vector<Face*>* faces;
};

#endif