
#include <iostream>
#include <iterator>

#include <cmath>

#include "City.h"
#include "House.h"
#include "../Geom/GeomOp.h"
#include "../Misc/Misc.h"

House::House()
{
	vertices = new std::vector<Vertex*>();
	faces = new std::vector<Face*>();
}

House::House(std::vector<Vertex*>* frontiers) : vertices(frontiers)
{
	faces = new std::vector<Face*>();
}

House::~House()
{
	delete vertices;
	delete faces;
}

void House::Build()
{
	if (sqrt(Surface(*vertices))/City::HumanSize >= 20.f)
	{
		//std::cout << "pyramid" << std::endl;
		CreatePyramid(0.2f);
	}
	else
	{
		//std::cout << "cube" << std::endl;
		//CreateCubeField(*vertices, 0.2f, rand_int(1,5)*City::HumanSize*2.f);
		CreatePyramid(0.2f);
	}
}

void House::CreateCubeField(std::vector<Vertex*>& vect, 
				double base, double height)
{
	Vertex *v000 = new Vertex(vect.at(0)->X(), vect.at(0)->Y(), base);
	Vertex *v100 = new Vertex(vect.at(1)->X(), vect.at(1)->Y(), base);
	Vertex *v010 = new Vertex(vect.at(3)->X(), vect.at(3)->Y(), base);
	Vertex *v110 = new Vertex(vect.at(2)->X(), vect.at(2)->Y(), base);
	Vertex *v001 = new Vertex(vect.at(0)->X(), vect.at(0)->Y(), height);
	Vertex *v101 = new Vertex(vect.at(1)->X(), vect.at(1)->Y(), height);
	Vertex *v011 = new Vertex(vect.at(3)->X(), vect.at(3)->Y(), height);
	Vertex *v111 = new Vertex(vect.at(2)->X(), vect.at(2)->Y(), height);
	std::vector<Vertex*>* tempFaceVert = new std::vector<Vertex*>();
	
	//bottom
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v110);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// up
	tempFaceVert->clear();
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v011);
	tempFaceVert->push_back(v101);
	tempFaceVert->push_back(v111);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// front
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v011);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
			
	// back
	tempFaceVert->clear();
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v110);
	tempFaceVert->push_back(v101);
	tempFaceVert->push_back(v111);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// left
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v101);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// right
	tempFaceVert->clear();
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v110);
	tempFaceVert->push_back(v011);
	tempFaceVert->push_back(v111);
	faces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
}

void House::CreateStep(std::vector<Vertex*>& vect, double base, double height)
{
	std::vector<Vertex*> ceiling;
	std::vector<Vertex*>::iterator itv;
	
	ceiling.clear();
	for (itv = vect.begin(); itv != vect.end(); ++itv)
	{
		ceiling.push_back(new Vertex((*itv)->X(), (*itv)->Y(), height));
	}
	ReArrangeBugged(ceiling);
	faces->push_back(new Face(new std::vector<Vertex*>(ceiling)));
	
	std::vector<Vertex*> *front;
	for (unsigned int i = 0; i < vect.size(); ++i)
	{
		/*front = new std::vector<Vertex*>();
		
		front->push_back(new Vertex(vect[i][0], vect[i][1], ));
		
		faces->push_back(new Face(front));
		
		*/
	}
	
	
}

void House::CreateWindow(Vertex &topLeft, Vertex &botRight)
{
	/*std::vector<Vertex*> vect;
	vect.push_back(new Vertex(topLeft));
	vect.push_back(new Vertex(botRight[0], ,topLeft[2]));
	vect.push_back(new Vertex(botRight));
	
	for (int i = 0; i < 4; i++)
	{
		
		
	}
	*/
}

void House::CreatePyramid(double stepDeep)
{
	CreateCubeField(*vertices, 0.f, 2.f);
	
	std::vector<Vertex*>::iterator itv;
	std::vector<Vertex*> tempVect;
	for (itv = vertices->begin(); itv != vertices->end(); ++itv)
		tempVect.push_back(new Vertex(*(*itv)));
	
	int i = 1;
	while (stepDeep * i < 1.0f)
	{
		//std::vector<Vertex*> temp = Shrink(tempVect, stepDeep);
		//CreateCubeField(temp, i*2.f, (i+1)*2.f);
		CreateStep(tempVect, i*2.f, (i+1)*2.f);
		i++;
	}
	
	tempVect.clear();
}
