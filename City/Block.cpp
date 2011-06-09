
#include <cmath>

#include "Block.h"
#include "../Geom/GeomOp.h"
#include "../Misc/Misc.h"
#include "../define.h"

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
		
		GenerateActualRepartition(houseFrontiers);
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
		ReArrange(*houseFrontiers);
		
		House* myHouse = new House(houseFrontiers);
		houses->push_back(myHouse);
	}
	
}


void Block::GenerateActualRepartition(std::vector<Vertex *> &vert)
{
	assert(vert.size() == 4);
	
	// max deep
	std::vector<Vertex *>::iterator itv;
	std::vector<Vertex *> deep;
	for (itv = vert.begin(); itv != vert.end(); ++itv)
	{
		deep.push_back(new Vertex(*(*itv)));
	}
	Shrink(deep, 0.5f);
	
	
	unsigned int n = vert.size();
	for (unsigned int i = 0; i < n; i++)
	{
		// angular house
		std::vector<Vertex *> *houseFr = new std::vector<Vertex *>();
		houseFr->push_back(new Vertex(*vert[(i+1)%n]));
		
		double distBC = sqrt(pow(Distance(*vert[(i+1)%n],*deep[(i+1)%n]),2)/2);
		Vertex vectBD(*deep[i]-*deep[(i+1)%n]);
		Vertex BC(*deep[(i+1)%n]);
		if (i % 2 == 0)
		{
			BC -= Normalized(Orthogonal(vectBD))*distBC;
		}
		else
		{
			BC += Normalized(Orthogonal(vectBD))*distBC;
		}
		
		houseFr->push_back(new Vertex(BC));
		houseFr->push_back(new Vertex(*deep[(i+1)%n]));
		
		Vertex BE(*deep[(i+1)%n]);
		BE -= Orthogonal(Normalized(Orthogonal(vectBD))*distBC);
		houseFr->push_back(new Vertex(BE));
		
		House *myHouse = new House(houseFr);
		
		houses->push_back(myHouse);
		
		// other houses
		double hss = (double)rand_int(2,5);
		std::vector<Vertex*> pointsHouses;
		double alea;
		for (int u = 0; u <= hss; u++)
		{
			alea = u/hss + rand_double(-1/(hss*2.f),1/(hss*2.f));
			pointsHouses.push_back(PointOnALine(*deep[i], 
							    *deep[(i+1)%n], alea));
		}
		
		for (unsigned int v = 0; v < pointsHouses.size() -1; v++)
		{
			if (rand_int(0,5) != 0)
			{
				std::vector<Vertex*> *houseFr = new std::vector<Vertex*>();
				houseFr->push_back(pointsHouses.at(v));
				houseFr->push_back(pointsHouses.at(v+1));
				
				Vertex AB(*pointsHouses.at(v+1)-*pointsHouses.at(v));
				Vertex OrthoAB(Normalized(Orthogonal(AB))*distBC);
				Vertex newC(*pointsHouses.at(v+1));
				Vertex newD(*pointsHouses.at(v));
				if (i%2 == 0)
				{
					newC += OrthoAB;
					newD += OrthoAB;
				}
				else
				{
					newC -= OrthoAB;
					newD -= OrthoAB;
				}
				houseFr->push_back(new Vertex(newC));
				houseFr->push_back(new Vertex(newD));
				
				House *myHouse = new House(houseFr);
				houses->push_back(myHouse);
			}
		}
	} // end for
}

