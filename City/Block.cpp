
#include "Block.h"

Block::Block()
{
	//vertices = new std::vector<Vertex*>();
	//houses = new std::vector<House*>();
}

Block::Block(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	//houses = new std::vector<House*>();
}

Block::~Block()
{
	//delete vertices;
	//delete houses;
}

void Block::Generate()
{


}