
#include "Area.h"
#include "../Geom/GeomOp.h"

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
	CreateSquareBlocks(1);
	
	
	std::vector<Block*>::iterator iteBlock;
	for (iteBlock = blocks->begin(); iteBlock != blocks->end(); ++iteBlock)
	{
		(*iteBlock)->Generate();
	}
}

void Area::CreateSquareBlocks(int number)
{
	(void) number;
	//double threshold = number;
	//test block
	
	Vertex g(GravityCenter(*vertices));
	
	Vertex mid01(GravityCenter(vertices->at(0),vertices->at(1)));
	Vertex mid12(GravityCenter(vertices->at(1),vertices->at(2)));
	Vertex mid23(GravityCenter(vertices->at(2),vertices->at(3)));
	Vertex mid30(GravityCenter(vertices->at(3),vertices->at(0)));
	
	std::vector<Vertex*>* blockFrontiers;
	Block* myBlock;
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(*(vertices->at(0))));
	blockFrontiers->push_back(new Vertex(mid30[0], mid30[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid01[0], mid01[1], 0.f));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(mid12[0], mid12[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vertices->at(1))));
	blockFrontiers->push_back(new Vertex(mid01[0], mid01[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid23[0], mid23[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vertices->at(2))));
	blockFrontiers->push_back(new Vertex(mid12[0], mid12[1], 0.f));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(mid23[0], mid23[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid30[0], mid30[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vertices->at(3))));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
}









