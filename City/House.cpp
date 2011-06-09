
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
	{
		delete (*itv);
	}
	vertices->clear();
	
	std::vector<Face*>::iterator itf;
	for (itf = faces->begin(); itf != faces->end(); ++itf)
	{
		delete (*itf);
	}
	faces->clear();
	
	delete vertices;
	delete faces;
}

void House::Build()
{
	double max_step = 8.f;
	if (sqrt(Surface(*vertices))/City::HumanSize >= 20.f)
	{
		max_step = 3.f;
	}
	
	CreatePyramid(rand_double(1.f, max_step));
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
		double wins = Distance(vL,vR) / (height-base);
		
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
// style = 0 -> empty
// style = 1 -> 2 pan
// style = 2 -> 4 pan
{
	assert(base != height);
	assert(vect.size() == 4);
	
	std::vector<Vertex*> roofPan;
	
	if (style == 0)
		return;
	else if (style == 1)
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
	else if (style == 2)
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
	{
		window.push_back(new Vertex(*(*itv)));
	}
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
	std::vector<Vertex*>::iterator itv;
	std::vector<Vertex*> tempVect;
	for (itv = vertices->begin(); itv != vertices->end(); ++itv)
	{
		tempVect.push_back(new Vertex(*(*itv)));
	}
	
	// first step
	CreateStep(tempVect, 0.f, 3.f);
	
	// others steps
	int i;
	for (i = 1; i < stepDeep; i++)
	{
		CreateStep(tempVect, 1.f+i*2.f, 1.f+(i+1)*2.f);
	}
	
	// last step
	if (vertices->size() == 4)
	{
		CreateRoof(tempVect, rand_int(0,3), 1.f+i*2.f, 1.f+(i+2)*2.f);
	}
	else
	{
		CreateRoof(tempVect, 1, 1.f+i*2.f, 1.f+(i+2)*2.f);
	}
	
	for (itv = tempVect.begin(); itv != tempVect.end(); ++itv)
	{
		delete *itv;
	}
	tempVect.clear();
}
