
#include <iostream>
#include <iterator>
#include <cmath>

#include "City.h"
#include "../Geom/Vertex.h"
#include "../Geom/GeomOp.h"
#include "../Misc/Misc.h"
#include "../define.h"

double City::HumanSize = HUMAN_SIZE; // 2 mètres

City::City()
{
	size = CITY_SIZE;
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
	
	
	// ---------------------------------------------------------------------------
	std::vector<Area*>::iterator iteArea;
	for (iteArea = areas->begin(); iteArea != areas->end(); ++iteArea)
	{
		(*iteArea)->Subdivide();
	}
}

void City::CreateAreas(std::vector<Vertex*> &vertices)
{
	if (CITY_STYLE == 0)
	{
		CreateSquareAreas(vertices);
	}
	else if (CITY_STYLE == 1)
	{
		CreateStarAreas(vertices);
	}
	else if (CITY_STYLE == 2)
	{}
	
	double max_surface = MAX_AREA_SURFACE; // quartier 20 km2 max
	for (unsigned int i = 0; i < areas->size(); i++)
	{
		if (areas->at(i)->GetSurface() > max_surface)
		{
			std::vector<Vertex*>* frontiers = new std::vector<Vertex*>(areas->at(i)->GetVertices());
			delete areas->at(i);
			areas->erase(areas->begin() + i);
			
			// cutting the area
			CreateAreas(*frontiers);
		}
	}
	//std::cout << "number: " << areas->size() << std::endl;
}


void City::CreateSquareAreas(std::vector<Vertex*> &vertices)
{
	double rand = sqrt(Surface(vertices)) / 2 * ((EXTRA_CENTER_PERC)/2.f);
	Vertex gCenter(GravityCenter(vertices));
	Vertex center(	gCenter[0]+rand_double(-rand, rand), 
			gCenter[1]+rand_double(-rand, rand), 
			gCenter[2]+0.f);
	
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
		
		//std::cout << "surface: " << Surface(*areaFrontiers) << std::endl;
		myArea = new Area(areaFrontiers);
		areas->push_back(myArea);
	}
}

void City::CreateStarAreas(std::vector<Vertex*> &vertices)
{
	double rand = sqrt(Surface(vertices)) / 2 * ((EXTRA_CENTER_PERC)/2.f);
	Vertex gCenter(GravityCenter(vertices));
	Vertex center(	gCenter[0]+rand_double(-rand, rand), 
			gCenter[1]+rand_double(-rand, rand), 
			gCenter[2]+0.f);
	
	std::vector<Vertex*> *areaFrontiers;
	//Vertex *mid, *mid2;
	Area* myArea;
	
	// Generate Area
	for (int i = 0; i < 4; i++)
	{
		areaFrontiers = new std::vector<Vertex*>();
		
		areaFrontiers->push_back(new Vertex(center));
		areaFrontiers->push_back(vertices[i]);
		areaFrontiers->push_back(vertices[(i+1)%4]);
		/*mid = new Vertex(GravityCenter(vertices[i],
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
		areaFrontiers->push_back(mid2);*/
		//ReArrange(*areaFrontiers);
		
		std::cout << "surface: " << Surface(*areaFrontiers) << std::endl;
		myArea = new Area(areaFrontiers);
		areas->push_back(myArea);
	}
	
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