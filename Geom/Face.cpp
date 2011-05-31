
#include <iterator>

#include "Face.h"

Face::~Face()
{}

void Face::Translate(double x, double y, double z)
{
	std::vector<Vertex *>::iterator itv;
	for (itv = vertices->begin(); itv != vertices->end(); ++itv)
	{
		(*itv)->Translate(x, y, z);
	}
}