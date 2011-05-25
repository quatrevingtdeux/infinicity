
#include <iterator>
#include "GeomOp.h"

std::vector<Vertex*> &Shrink(std::vector<Vertex*> &vertices, double percentage)
{
	Vertex gravityCenter(0.f, 0.f, 0.f);
	int n = vertices.size();
	std::vector<Vertex*>::iterator itv;
	
	for (itv = vertices.begin(); itv != vertices.end(); ++itv)
	{
		gravityCenter[0] += (*itv)->X()/n;
		gravityCenter[1] += (*itv)->Y()/n;
		gravityCenter[2] += (*itv)->Z()/n;
	}
	
	Vertex temp(0.f, 0.f, 0.f);
	std::vector<Vertex*> normalVector;
	for (itv = vertices.begin(); itv != vertices.end(); ++itv)
	{
		temp[0] = gravityCenter[0] - (*itv)->X();
		temp[1] = gravityCenter[1] - (*itv)->Y();
		temp[2] = gravityCenter[2] - (*itv)->Z();
		normalVector.push_back(new Vertex(temp));
	}
	
	std::vector<Vertex*> resizedVector;
	for (itv = vertices.begin(); itv != vertices.end(); ++itv)
	{
		temp = *(*itv);
		temp[0] += percentage * (*itv)->X();
		temp[1] += percentage * (*itv)->Y();
		temp[2] += percentage * (*itv)->Z();
		delete (*itv);
		(*itv) = new Vertex(temp);
	}
	
	return vertices;
	
}