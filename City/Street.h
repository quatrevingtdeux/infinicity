#ifndef STREET_H
#define STREET_H

#include "../Geom/Vertex.h"

class Street
{
	public:
		Street();
		~Street();
	
	private:
		Vertex begin;
		Vertex end;
		double width;
};

#endif