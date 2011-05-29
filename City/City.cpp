
#include <iostream>
#include <iterator>
#include <cmath>

#include "City.h"
#include "../Geom/Vertex.h"
#include "../Geom/GeomOp.h"
#include "../Misc/Misc.h"

double City::HumanSize = 1.0f; // 2 mètres

City::City()
{
	size = 4000.0f;
	frontiers = new std::vector<Vertex*>();
	areas = new std::vector<Area*>();
}

City::City(double size) : size(size)
{
	frontiers = new std::vector<Vertex*>();
	areas = new std::vector<Area*>();
}

City::~City()
{
	areas->clear();
	frontiers->clear();
	delete areas;
	delete frontiers;
}

void City::Generate()
{
	// Generate Frontiers
	frontiers->push_back(new Vertex(-size/2.f, -size/2.f, 0.f));
	frontiers->push_back(new Vertex( size/2.f, -size/2.f, 0.f));
	frontiers->push_back(new Vertex( size/2.f,  size/2.f, 0.f));
	frontiers->push_back(new Vertex(-size/2.f,  size/2.f, 0.f));
	
	
	// Creating areas
	CreateAreas(*frontiers);
	
	std::vector<Area*>::iterator iteArea;
	for (iteArea = areas->begin(); iteArea != areas->end(); ++iteArea)
	{
		(*iteArea)->Subdivide();
	}
}

void City::CreateAreas(std::vector<Vertex*> &vertices)
{
	double rand = size / HumanSize * 0.2f;
	Vertex center(rand_double(-rand, rand), rand_double(-rand, rand), 0.f);
	//Vertex mid(5.f, 5.f, 0.f);
	
	std::vector<Vertex*> *areaFrontiers;
	Vertex *mid, *mid2;
	Area* myArea;
	
	// Generate Area
	for (int i = 0; i < 4; i++)
	{
		areaFrontiers = new std::vector<Vertex*>();
		
		areaFrontiers->push_back(new Vertex(center));
		areaFrontiers->push_back(vertices[i]);
		mid = new Vertex(GravityCenter(vertices[i],
					       vertices[(i+1)%4]));
		areaFrontiers->push_back(mid);
		
		int n = (i - 1) % 4;
		if (n < 0)
		{
			mid2 = new Vertex(GravityCenter(vertices[i],
							vertices[4 + n]));
		}
		else
		{
			mid2 = new Vertex(GravityCenter(vertices[i],
							vertices[n]));
		}
		areaFrontiers->push_back(mid2);
		ReArrange(*areaFrontiers);
		myArea = new Area(areaFrontiers);
		areas->push_back(myArea);
	}
	
	/*double max_surface = HumanSize * 10000000.f;
	for (unsigned int i = 0; i < areas->size(); i++)
	{
		std::cout << areas->at(i)->GetSurface() << std::endl;
		if (areas->at(i)->GetSurface() > max_surface)
		{
			// cutting the area
			CreateAreas(areas->at(i)->GetVertices());
		}
	}*/
}






















std::vector<Face*>* City::GetFaces() const
{
	std::vector<Area*>::iterator iteArea;
	std::vector<Block*>::iterator iteBlock;
	std::vector<House*>::iterator iteHouse;
	std::vector<Street*>::iterator iteStreet;
	std::vector<Block*> blocks;
	std::vector<House*> houses;
	std::vector<Street*> streets;
	
	std::vector<Face*>::iterator iteFace;
	std::vector<Face*> objectFaces;
	
	std::vector<Face*>* faces = new std::vector<Face*>();
	
	for (iteArea = areas->begin(); iteArea != areas->end(); ++iteArea)
	{
		blocks = (*iteArea)->GetBlocks();
		for (iteBlock = blocks.begin(); iteBlock != blocks.end(); ++iteBlock)
		{
			houses = (*iteBlock)->GetHouses();
			for (iteHouse = houses.begin(); 
			     iteHouse != houses.end(); ++iteHouse)
			{
				objectFaces = (*iteHouse)->GetFaces();
				for (iteFace = objectFaces.begin(); 
				     iteFace != objectFaces.end(); ++iteFace)
				{
					faces->push_back((*iteFace));
				}
			}
			
			streets = (*iteBlock)->GetStreets();
			for (iteStreet = streets.begin(); 
			     iteStreet != streets.end(); ++iteStreet)
			{
				objectFaces = (*iteStreet)->GetFaces();
				for (iteFace = objectFaces.begin(); 
				     iteFace != objectFaces.end(); ++iteFace)
				{
					faces->push_back((*iteFace));
				}
			}
		}
	}
	
	return faces;
}