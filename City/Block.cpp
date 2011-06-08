
#include <iostream>
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
		//if (rand_int(0,2) == 0)
		//	GenerateCourtyard4Edges(houseFrontiers);
		//else
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
	/*
	Vertex *v1 = PointOnALine(*vertices[0], *vertices[1], 0.5f);
	Vertex *v2 = PointOnALine(*vertices[0], *vertices[3], 0.5f);
	//Vertex *mid = new Vertex(GravityCenter(v1, v2));
	
	std::vector<Vertex *> vect;
	vect.push_back(vertices[0]);
	vect.push_back(v1);
	//vect.push_back(mid);
	vect.push_back(v2);
	
	House* myStreet = new House(new std::vector<Vertex*>(vect));
	houses->push_back(myStreet);
	
	*/
	
		
	
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
		deep.push_back(new Vertex(*(*itv)));
	Shrink(deep, 0.5f);
	
	
	unsigned int n = vert.size();
	for (unsigned int i = 0; i < n; i++)
	{
		/* seguier method */
		// angular house
		std::vector<Vertex *> *houseFr = new std::vector<Vertex *>();
		houseFr->push_back(new Vertex(*vert[(i+1)%n]));
		
		
		double distBC = sqrt(pow(Distance(*vert[(i+1)%n],*deep[(i+1)%n]),2)/2);
		Vertex vectBD(*deep[i]-*deep[(i+1)%n]);
		Vertex BC(*deep[(i+1)%n]);
		if (i%2 == 0)
			BC -= Normalized(Orthogonal(vectBD))*distBC;
		else
			BC += Normalized(Orthogonal(vectBD))*distBC;
		houseFr->push_back(new Vertex(BC));
		houseFr->push_back(new Vertex(*deep[(i+1)%n]));
		
		Vertex BE(*deep[(i+1)%n]);
		BE -= Orthogonal(Normalized(Orthogonal(vectBD))*distBC);
		houseFr->push_back(new Vertex(BE));
		
		House *myHouse = new House(houseFr);
		
		houses->push_back(myHouse);
		
		
		//double hss = Distance(*deep[i], *deep[(i+1)%n]) / MIN_HOUSE_WIDTH;
		double hss = 4;
		std::vector<Vertex*> pointsHouses;
		for (int u = 0; u < hss; u++)
		{
			pointsHouses.push_back(PointOnALine(*deep[i], 
							    *deep[(i+1)%n], u/hss));
		}
		/*
		for (unsigned int v = 0; v < pointsHouses.size()-1; v++)
		{
			std::vector<Vertex*> *houseFr = new std::vector<Vertex*>();
			houseFr->push_back(pointsHouses.at(v));
			houseFr->push_back(pointsHouses.at(v+1));
			
			Vertex AB(*pointsHouses.at(v+1)-*pointsHouses.at(v));
			Vertex OrthoAB(Normalized(Orthogonal(AB))*distBC);
			Vertex newC(*pointsHouses.at(v+1));
			newC += OrthoAB;
			
			houseFr->push_back(new Vertex(newC));
			Vertex newD(*pointsHouses.at(v+1));
			newD -= OrthoAB;
			houseFr->push_back(new Vertex(newD));
			
			House *myHouse = new House(houseFr);
			houses->push_back(myHouse);
			
			
		}*/
		
		
		
		/*
		
		double dist = Distance(*vert[i], *vert[(i+1)%n]) * 0.8f;
		double percMin = 0.1f;
		double percMax = 0.3f;
		double currPerc;
		
		double sum = 0.1f;
		while (sum < 0.9f)
		{
			currPerc = rand_double(percMin, percMax);
			if (sum + currPerc + percMin > 0.9f)
				currPerc = 0.9f - sum;
			
			std::cout << "sum " << sum << std::endl;
			std::cout << "currPerc" << currPerc << std::endl;
			
			
			std::vector<Vertex *> *houseFrontiers = 
						new std::vector<Vertex *>();
			Vertex *first = PointOnALine(*vert[i], 
						     *vert[(i+1)%n], sum);
			houseFrontiers->push_back(first);
			Vertex *second = PointOnALine(*vert[i], 
						      *vert[(i+1)%n], sum+currPerc);
			houseFrontiers->push_back(second);
			
			Vertex *sdShr = PointOnALine(*deep[i], 
						     *deep[(i+1)%n], sum+currPerc);
			houseFrontiers->push_back(sdShr);
			Vertex *fstShr = PointOnALine(*deep[i], 
						      *deep[(i+1)%n], sum);
			houseFrontiers->push_back(fstShr);
			//ReArrange(*houseFrontiers);
			
			House *myHouse = new House(houseFrontiers);
			houses->push_back(myHouse);
			
			sum += currPerc;
		}
		std::cout << std::endl;
		*/
		
		// angular houses	
	}
	
	
	
}