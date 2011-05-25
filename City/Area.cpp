
#include "Area.h"

Area::Area()
{
	blocks = new std::vector<Block*>();
	
}

Area::Area(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	blocks = new std::vector<Block*>();
}

Area::~Area()
{
	delete blocks;
	
}

void Area::Subdivide()
{
	//test block
	std::vector<Vertex*>* blockFrontiers = new std::vector<Vertex*>(*vertices);
	Block* myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	std::vector<Block*>::iterator iteBlock;
	for (iteBlock = blocks->begin(); iteBlock != blocks->end(); ++iteBlock)
	{
		(*iteBlock)->Generate();
	}
}