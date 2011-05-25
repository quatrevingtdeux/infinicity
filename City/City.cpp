
#include <iterator>
#include <ctime>

#include "City.h"
#include "../Geom/Vertex.h"

City::City()
{
	// here for personnalisation variables
	size = 40.0f;
	humanSize = 1.0f; // 2 mètres
	frontiers = new std::vector<Vertex*>();
	areas = new std::vector<Area*>();
}

City::City(double size, double humanSize) : size(size), humanSize(humanSize)
{
	frontiers = new std::vector<Vertex*>();
	areas = new std::vector<Area*>();
}

City::~City()
{
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
	
	//test area
	std::vector<Vertex*>* areaFrontiers;
	Area* myArea;
	
	areaFrontiers = new std::vector<Vertex*>();
	areaFrontiers->push_back(new Vertex(	-size/2.f,	-size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex( 	      0.f,	-size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex( 	      0.f,	 size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex(	-size/2.f,	 size/2.f, 0.f));
	myArea = new Area(areaFrontiers);
	areas->push_back(myArea);
	
	areaFrontiers = new std::vector<Vertex*>();
	areaFrontiers->push_back(new Vertex(	     0.f,	-size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex(	size/2.f,	-size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex(	size/2.f,	 size/2.f, 0.f));
	areaFrontiers->push_back(new Vertex(	     0.f,	 size/2.f, 0.f));
	myArea = new Area(areaFrontiers);
	areas->push_back(myArea);
	
	
	
	std::vector<Area*>::iterator iteArea;
	for (iteArea = areas->begin(); iteArea != areas->end(); ++iteArea)
	{
		(*iteArea)->Subdivide();
	}
	
	/*
	// Generate Area	
	for (int i = 0; i < 4; ++i)
	{
		areas.push_back(new Area());
	}
	
	for (std::vector<Area*>::iterator it = areas.begin();
		it != areas.end(); ++it)
	{
		(*it)->Subdivide();
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

















