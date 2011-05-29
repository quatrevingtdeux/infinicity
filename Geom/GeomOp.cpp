
#include <iterator>
#include "GeomOp.h"

std::vector<Vertex*> &Shrink(std::vector<Vertex*> &vertices, double percentage)
{
	std::vector<Vertex*>::iterator itv;
	
	Vertex gravityCenter(GravityCenter(vertices));
	
	// calcul des normales au point vers le centre de gravité
	Vertex temp(0.f, 0.f, 0.f);
	std::vector<Vertex*> normalVertex;
	for (itv = vertices.begin(); itv != vertices.end(); ++itv)
	{
		temp[0] = gravityCenter[0] - (*itv)->X();
		temp[1] = gravityCenter[1] - (*itv)->Y();
		temp[2] = gravityCenter[2] - (*itv)->Z();
		normalVertex.push_back(new Vertex(temp));
	}
	
	// calcul des nouveaux points avec un pourcentage des normales au point
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		temp = *(vertices[i]);
		temp[0] += percentage * normalVertex[i]->X();
		temp[1] += percentage * normalVertex[i]->Y();
		temp[2] += percentage * normalVertex[i]->Z();
		delete normalVertex[i];
		// delete vertices[1];
		*(vertices[i]) = temp;
	}
	
	return vertices;
}

Vertex GravityCenter(std::vector<Vertex*> &vertices)
{
	// calcul du centre de gravité de la face
	Vertex gravityCenter(0.f, 0.f, 0.f);
	int n = vertices.size();
	std::vector<Vertex*>::iterator itv;
	
	for (itv = vertices.begin(); itv != vertices.end(); ++itv)
	{
		gravityCenter[0] += (*itv)->X()/n;
		gravityCenter[1] += (*itv)->Y()/n;
		gravityCenter[2] += (*itv)->Z()/n;
	}
	
	return gravityCenter;	
}

Vertex GravityCenter(Vertex *vertex1, Vertex *vertex2)
{
	std::vector<Vertex*> vertices;
	vertices.push_back(vertex1);
	vertices.push_back(vertex2);
	
	return GravityCenter(vertices);
}