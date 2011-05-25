
#include "Block.h"

Block::Block()
{
	vertices = new std::vector<Vertex*>();
	houses = new std::vector<House*>();
}

Block::Block(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	houses = new std::vector<House*>();
}

Block::~Block()
{
	delete vertices;
	delete houses;
}

void Block::Generate()
{
	std::vector<Vertex*>* houseFrontiers = new std::vector<Vertex*>(*vertices);
	House* myHouse = new House(houseFrontiers);
	houses->push_back(myHouse);
	
	std::vector<House*>::iterator iteHouse;
	for (iteHouse = houses->begin(); iteHouse != houses->end(); ++iteHouse)
	{
		(*iteHouse)->Build();
	}
}