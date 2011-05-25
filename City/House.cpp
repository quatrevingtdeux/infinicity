
#include "House.h"

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
	CreateCubeField();
}

void House::CreateCubeField()
{
	double height = 2.0f;
	Vertex *v000 = new Vertex(vertices->at(0)->X(), vertices->at(0)->Y(), 0.f);
	Vertex *v100 = new Vertex(vertices->at(1)->X(), vertices->at(1)->Y(), 0.f);
	Vertex *v010 = new Vertex(vertices->at(3)->X(), vertices->at(3)->Y(), 0.f);
	Vertex *v110 = new Vertex(vertices->at(2)->X(), vertices->at(2)->Y(), 0.f);
	Vertex *v001 = new Vertex(vertices->at(0)->X(), vertices->at(0)->Y(), height);
	Vertex *v101 = new Vertex(vertices->at(1)->X(), vertices->at(1)->Y(), height);
	Vertex *v011 = new Vertex(vertices->at(3)->X(), vertices->at(3)->Y(), height);
	Vertex *v111 = new Vertex(vertices->at(2)->X(), vertices->at(2)->Y(), height);
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