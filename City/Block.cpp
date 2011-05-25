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
	
	// houses
	
	std::vector<Vertex*>* houseFrontiers = new std::vector<Vertex*>(*vertices);
	std::cout << " size befor shrink : " << (*houseFrontiers->back())[0] << std::endl;
	Shrink(*houseFrontiers, 0.5f);
	std::cout << " size after shrink : " << (*houseFrontiers->back())[0] << std::endl;
	House* myHouse = new House(houseFrontiers);
	houses->push_back(myHouse);
	
	// streets
	std::vector<Vertex*>* streetFrontiers = new std::vector<Vertex*>(*vertices);
	Street* myStreet = new Street(streetFrontiers);
	streets->push_back(myStreet);
	
	
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