
#include <iostream>
#include <iterator>
#include <cassert>

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
	std::vector<Vertex*>::iterator itv;
	for (itv = vertices->begin(); itv != vertices->end(); ++itv)
		delete (*itv);
	vertices->clear();
	
	std::vector<Face*>::iterator itf;
	for (itf = faces->begin(); itf != faces->end(); ++itf)
		delete (*itf);
	faces->clear();
	
	delete vertices;
	delete faces;
}

void House::Build()
{
	if (sqrt(Surface(*vertices))/City::HumanSize >= 20.f)
	{
		//std::cout << "pyramid" << std::endl;
		//CreatePyramid(0.2f);
		//CreateCubeField(*vertices, 0.2f, 20.f);
	}
	else
	{
		//std::cout << "cube" << std::endl;
		
		//CreatePyramid(rand_double(0.1f, 0.8f));
	}
	
	//CreateCubeField(*vertices, 0.2f, 2.f);
	CreatePyramid(rand_double(0.1f, 0.16f));
}


void House::CreateCubeField(std::vector<Vertex*>& vect, 
				double base, double height)
{
	// TEST FUNCTION, DON'T WASTE TIME TO CLEAN
	assert(vect.size() == 4);
	
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
	assert(base != height);
	
	std::vector<Vertex*> ceiling;
	
	for (int i = 0; i < 4; i++)
	{
		int u = (i == 2) ? 3 : ((i == 3) ? 2 : i);
		ceiling.push_back(new Vertex((vect[u])->X(), (vect[u])->Y(), height));
	}
	faces->push_back(new Face(new std::vector<Vertex*>(ceiling)));
	
	unsigned int n = vect.size();
	for (unsigned int i = 0; i < n; ++i)
	{
		Vertex vL(*(vect[i]));
		Vertex vR(*(vect[(i+1)%n]));
		int wins = Distance(vL,vR) / (height-base);
		
		if (wins == 1)
		{
			Vertex *v = PointOnALine(vL, vR, 0.5f);
			CreateWindow(vL, *v, base, height);
			CreateWindow(*v, vR, base, height);
			delete v;
		}
		else
		{
			double step =  1.f / wins;
			double currentS = step;
			Vertex *v = PointOnALine(vL, vR, currentS);
			Vertex *v2;
			CreateWindow(vL, *v, base, height);
			
			for (int i = 0; i < wins-2; i++)
			{
				currentS += step;
				v2 = PointOnALine(vL, vR , currentS);
				CreateWindow(*v, *v2, base, height);
				delete v;
				v = v2;
			}
			
			CreateWindow(*v, vR, base, height);
			delete v;
		}
	}
}


void House::CreateRoof(std::vector<Vertex*> &vect, int style,
		       double base, double height)
// style = 0 -> 2 pans
// style = 1 -> pyramidal
{
	assert(base != height);
	assert(vect.size() == 4);
	assert(style < 2);
	
	std::vector<Vertex*> roofPan;
	
	if (style == 0)
	{
		Vertex mid1(GravityCenter(vect[0], vect[1]));
		Vertex mid2(GravityCenter(vect[2], vect[3]));
		
		roofPan.push_back(new Vertex(vect[0]->X(), vect[0]->Y(), base));
		roofPan.push_back(new Vertex(mid1.X(), mid1.Y(), height));
		roofPan.push_back(new Vertex(vect[3]->X(), vect[3]->Y(), base));
		roofPan.push_back(new Vertex(mid2.X(), mid2.Y(), height));
		faces->push_back(new Face(new std::vector<Vertex*>(roofPan)));
		
		roofPan.clear();
		roofPan.push_back(new Vertex(vect[1]->X(), vect[1]->Y(), base));
		roofPan.push_back(new Vertex(mid1.X(), mid1.Y(), height));
		roofPan.push_back(new Vertex(vect[2]->X(), vect[2]->Y(), base));
		roofPan.push_back(new Vertex(mid2.X(), mid2.Y(), height));
		faces->push_back(new Face(new std::vector<Vertex*>(roofPan)));
		
		roofPan.clear();
		roofPan.push_back(new Vertex(vect[0]->X(), vect[0]->Y(), base));
		roofPan.push_back(new Vertex(mid1.X(), mid1.Y(), height));
		roofPan.push_back(new Vertex(vect[1]->X(), vect[1]->Y(), base));
		faces->push_back(new Face(new std::vector<Vertex*>(roofPan)));
		
		roofPan.clear();
		roofPan.push_back(new Vertex(vect[2]->X(), vect[2]->Y(), base));
		roofPan.push_back(new Vertex(mid2.X(), mid2.Y(), height));
		roofPan.push_back(new Vertex(vect[3]->X(), vect[3]->Y(), base));
		faces->push_back(new Face(new std::vector<Vertex*>(roofPan)));
	}
	else if (style == 1)
	{
		Vertex cen(GravityCenter(vect));
		
		unsigned int n = vect.size();
		for(unsigned int i = 0; i < n; i++)
		{
			roofPan.clear();
			roofPan.push_back(new Vertex(vect[i]->X(), 
						     vect[i]->Y(), base));
			roofPan.push_back(new Vertex(vect[(i+1)%n]->X(), 
						     vect[(i+1)%n]->Y(), base));
			roofPan.push_back(new Vertex(cen.X(), cen.Y(), height));
			faces->push_back(new Face(new std::vector<Vertex*>(roofPan)));
		}
	}
}


void House::CreateWindow(Vertex &vL, Vertex &vR, double base, double height)
{
	std::vector<Vertex*> front;
	front.push_back(new Vertex(vL.X(), vL.Y(), base));
	front.push_back(new Vertex(vL.X(), vL.Y(), height));
	front.push_back(new Vertex(vR.X(), vR.Y(), height));
	front.push_back(new Vertex(vR.X(), vR.Y(), base));
	
	std::vector<Vertex*> window;
	std::vector<Vertex*>::iterator itv;
	for (itv = front.begin(); itv != front.end(); ++itv)
		window.push_back(new Vertex(*(*itv)));
	Shrink(window, 0.6f);
	
	std::vector<Vertex*>* pan;
	for (int i = 0; i < 4; i++)
	{
		pan = new std::vector<Vertex*>();
		
		pan->push_back(new Vertex(*(front[i])));
		pan->push_back(new Vertex(*(front[(i+1)%4])));
		pan->push_back(new Vertex(*(window[i])));
		pan->push_back(new Vertex(*(window[(i+1)%4])));
		
		faces->push_back(new Face(pan));
	}
}

void House::CreatePyramid(double stepDeep)
{
	//CreateCubeField(*vertices, 0.f, 2.f);
	
	std::vector<Vertex*>::iterator itv;
	std::vector<Vertex*> tempVect;
	for (itv = vertices->begin(); itv != vertices->end(); ++itv)
		tempVect.push_back(new Vertex(*(*itv)));
	
	// first step
	CreateStep(tempVect, 0.f, 3.f);
	
	// others steps
	int i = 1;
	while (stepDeep * i < 1.0f)
	{
		//std::vector<Vertex*> temp = Shrink(tempVect, stepDeep);
		//CreateCubeField(temp, i*2.f, (i+1)*2.f);
		CreateStep(tempVect, 1.f+i*2.f, 1.f+(i+1)*2.f);
		i++;
	}
	if (vertices->size() == 4)
	{
		CreateRoof(tempVect, rand_int(0,2), 1.f+i*2.f, 1.f+(i+2)*2.f);
	}
	else
		CreateRoof(tempVect, 1, 1.f+i*2.f, 1.f+(i+2)*2.f);
	
	tempVect.clear();
}
