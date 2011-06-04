
#include <iostream>

#include "Block.h"
#include "../Geom/GeomOp.h"

Block::Block()
{
	vertices = new std::vector<Vertex*>();
	houses = new std::vector<House*>();
	streets = new std::vector<Street*>();
}

Block::Block(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	houses = new std::vector<House*>();
	streets = new std::vector<Street*>();
}

Block::~Block()
{
	delete vertices;
	delete houses;
	delete streets;
}

void Block::Generate()
{
	std::vector<Vertex*>::iterator itv;
	
	// streets
	std::vector<Vertex*>* streetFrontiers = new std::vector<Vertex*>(*vertices);
	Street* myStreet = new Street(streetFrontiers);
	streets->push_back(myStreet);
	
	// houses	
	if (vertices->size() == 4)
	{
		std::vector<Vertex*> houseFrontiers;
		for (itv = vertices->begin(); itv != vertices->end(); ++itv)
			houseFrontiers.push_back(new Vertex(*(*itv)));
		Shrink(houseFrontiers, 0.2f);
		GenerateCourtyard4Edges(houseFrontiers);
	}
	
	// ---------------------------------------------------------------------------
	// building
	std::vector<House*>::iterator iteHouse;
	for (iteHouse = houses->begin(); iteHouse != houses->end(); ++iteHouse)
	{
		(*iteHouse)->Build();
	}
	
	std::vector<Street*>::iterator iteStreet;
	for (iteStreet = streets->begin(); iteStreet != streets->end(); ++iteStreet)
	{
		(*iteStreet)->Build();
	}
}

void Block::GenerateCourtyard4Edges(std::vector<Vertex*> &vertices)
{
	
	House* myStreet = new House(new std::vector<Vertex*>(vertices));
	houses->push_back(myStreet);
	/*	
	
	Vertex g(GravityCenter(vertices));
	Vertex *mid, *mid2;
	std::vector<Vertex*>* houseFrontiers;
	
	for (int i = 0; i < 4; i++)
	{
		houseFrontiers = new std::vector<Vertex*>();
		
		houseFrontiers->push_back(new Vertex(g));
		houseFrontiers->push_back(vertices[i]);
		mid = new Vertex(GravityCenter(vertices[i],
					       vertices[(i+1)%4]));
		houseFrontiers->push_back(mid);
		
		int n = (i - 1) % 4;
		if (n < 0)
			mid2 = new Vertex(GravityCenter(vertices[i], vertices[4 + n]));
		else
			mid2 = new Vertex(GravityCenter(vertices[i], vertices[n]));
		
		houseFrontiers->push_back(mid2);
		ReArrangeBugged(*houseFrontiers);
		
		House* myHouse = new House(houseFrontiers);
		houses->push_back(myHouse);
	}
	
	*/
}
