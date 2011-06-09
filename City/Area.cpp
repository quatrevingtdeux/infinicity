
#include "Area.h"
#include "../Geom/GeomOp.h"
#include "../Misc/Misc.h"
#include "../define.h"

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
	if (vertices->size() == 4)
	{
		CreateSquareBlocks(*vertices);
	}
	else
	{
		CreateTriangleBlocks(*vertices);
	}
	
	// ---------------------------------------------------------------------------	
	std::vector<Block*>::iterator iteBlock;
	for (iteBlock = blocks->begin(); iteBlock != blocks->end(); ++iteBlock)
	{
		(*iteBlock)->Generate();
	}
}

void Area::CreateSquareBlocks(std::vector<Vertex *> &vert)
{
	assert(vert.size() == 4);	
	
	//test block
	Vertex g(GravityCenter(vert));
	
	Vertex mid01(GravityCenter(vert[0], vert[1]));
	Vertex mid12(GravityCenter(vert[1], vert[2]));
	Vertex mid23(GravityCenter(vert[2], vert[3]));
	Vertex mid30(GravityCenter(vert[3], vert[0]));
	
	std::vector<Vertex*>* blockFrontiers;
	Block* myBlock;
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(*(vert[0])));
	blockFrontiers->push_back(new Vertex(mid30[0], mid30[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid01[0], mid01[1], 0.f));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(mid12[0], mid12[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vert[1])));
	blockFrontiers->push_back(new Vertex(mid01[0], mid01[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid23[0], mid23[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vert[2])));
	blockFrontiers->push_back(new Vertex(mid12[0], mid12[1], 0.f));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
	
	blockFrontiers = new std::vector<Vertex*>();
	blockFrontiers->push_back(new Vertex(mid23[0], mid23[1], 0.f));
	blockFrontiers->push_back(new Vertex(g));
	blockFrontiers->push_back(new Vertex(mid30[0], mid30[1], 0.f));
	blockFrontiers->push_back(new Vertex(*(vert[3])));
	myBlock = new Block(blockFrontiers);
	blocks->push_back(myBlock);
}

void Area::CreateTriangleBlocks(std::vector<Vertex *> &vert)
{
	assert(vert.size() == 3);
	
	unsigned int aCute = 0, a1 = 1, a2 = 2;
	
	while (AngleOfView(*vert[aCute], *vert[a1], *vert[a2]) > 60.f)
	{
		aCute = (aCute + 1) % 3;
		a1 = (a1 + 1) % 3;
		a2 = (a2 + 1) % 3;
	}
	
	double percMin = MIN_BLOCK_SURFACE / Surface(vert);
	double percMax = MAX_BLOCK_SURFACE / Surface(vert);
	
	percMax = (percMax > 1.f) ? 1.f : percMax;
	assert(percMin <= 1.0f);
	
	double actualPerc1 = rand_double(percMin, percMax);
	double actualPerc2 = rand_double(percMin, percMax);
	
	std::vector<Vertex *> *triangleBlock = new std::vector<Vertex *>();
	triangleBlock->push_back(new Vertex(*vert[aCute]));
	Vertex *a = PointOnALine(*vert[aCute], *vert[a1], actualPerc1);
	triangleBlock->push_back(new Vertex(*a));
	Vertex *b = PointOnALine(*vert[aCute], *vert[a2], actualPerc2);
	triangleBlock->push_back(new Vertex(*b));
	blocks->push_back(new Block(triangleBlock));
	
	std::vector<Vertex *> vect;
	vect.push_back(a);
	vect.push_back(vert[a1]);
	vect.push_back(vert[a2]);
	vect.push_back(b);
	CreateSquareBlocks(vect);
}

