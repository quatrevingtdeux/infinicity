#include <iostream>

#include "Street.h"
#include "../ObjManager/ImportObj.h"
#include "../define.h"
#include "../Geom/GeomOp.h"

Street::Street()
{
	vertices = new std::vector<Vertex*>();
	faces = new std::vector<Face*>();
}

Street::Street(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	faces = new std::vector<Face*>();
}

Street::~Street()
{
	delete vertices;
	delete faces;
}

void Street::Build()
{
	if (vertices->size() == 4)
		CreatePlaneStreet();
	else if (vertices->size() == 3)
		CreateTriangleStreet();
}

void Street::CreatePlaneStreet()
{
	double height = 0.2f;
	std::vector<Vertex *> vert;
	for (int i = 0; i < 4; i++)
	{
		// TODO lol refaire
		// anti bug trick
		int u = (i == 2) ? 3 : ((i == 3) ? 2 : i);
		Vertex *tmp = vertices->at(u);
		vert.push_back(new Vertex(tmp->X(), tmp->Y(), height));
	}
	faces->push_back(new Face(new std::vector<Vertex *>(vert)));
	
	// TODO ajouter trottoir
	
	
	// add tree
	ImportObj tree(TREE_FILE);
	std::vector<Face*>::iterator itf;
	std::vector<Face*> treefaces = tree.GetFaces();
	Vertex* v;
	for (itf = treefaces.begin(); itf != treefaces.end(); ++itf)
	{
		v = vertices->at(0);
		(*itf)->Translate(v->X(), v->Y(), v->Z());
		faces->push_back((*itf));	
	}
}

void Street::CreateTriangleStreet()
{
	assert(vertices->size() == 3);
	
	std::cout << "triangle street" << std::endl;
	double height = 0.2f;
	std::vector<Vertex *> vert;
	for (int i = 0; i < 3; i++)
	{
		Vertex *tmp = vertices->at(i);
		vert.push_back(new Vertex(tmp->X(), tmp->Y(), height));
	}
	
	faces->push_back(new Face(new std::vector<Vertex *>(vert)));
}

