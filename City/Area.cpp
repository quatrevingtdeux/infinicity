
#include "Area.h"

Area::Area()
{}

Area::Area(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{}

Area::~Area()
{}

void Area::Subdivide()
{
	//test block
	std::vector<Vertex*>* blockFrontiers = new std::vector<Vertex*>(*vertices);
	Block* myBlock = new Block(blockFrontiers);
	blocks.push_back(myBlock);
	blocks[0]->Generate();
}