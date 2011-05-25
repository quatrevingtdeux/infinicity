
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "ExportObj.h"

void ExportObj::Export(City* city)
{
	file.open(filename.c_str());
	if (file == NULL)
	{
		std::cerr << "Unable to create OBJ file" << std::endl;
		exit(EXIT_FAILURE);
	}
	(void)city;
	
	std::cout << "write in " << filename << std::endl;
	
	file << "# " << filename << std::endl << "# " << std::endl;
	file << std::endl << "g city" << std::endl << std::endl;
	
	// export
	//ExportFaces(city->GetFaces());
	
	ExportTestCube(CreateTestCube());
	
	file << std::endl;
	
	file.close();
}


void ExportObj::ExportFaces(std::vector<Face*>* faces)
{
	// writing vertices
	(void) faces;
	
	
	// writing faces
	
	
}


void ExportObj::ExportTestCube(std::vector<Face*>* faces)
{
	std::vector<Face*>::iterator iteFace;
	std::vector<Vertex*>::iterator iteVertex;
	std::vector<Vertex*> tpVert;
	double x, y, z;
	
	// writing vertices
	for (iteFace = faces->begin(); iteFace != faces->end(); ++iteFace)
	{
		tpVert = (*iteFace)->GetVertices();
		
		for (iteVertex = tpVert.begin(); 
		     iteVertex != tpVert.end(); ++iteVertex)
		{
			x = (*iteVertex)->X();
			y = (*iteVertex)->Y();
			z = (*iteVertex)->Z();
			file << "v  " << x << "  " << y << "  " << z << std::endl;
		}
	}
	
	// writing faces
	int next_id = 1;
	int id1, id2, id3;
	
	for (iteFace = faces->begin(); iteFace != faces->end(); ++iteFace)
	{
		id1 = next_id;
		id2 = next_id + 1;
		id3 = next_id + 3;
		file << "f  " << id1 << "//  " << id2 << "//  ";
		file << id3 << "// " << std::endl;
		
		id1 = next_id;
		id2 = next_id + 2;
		id3 = next_id + 3;
		file << "f  " << id1 << "//  " << id2 << "//  ";
		file << id3 << "// " << std::endl;
		
		next_id += 4;
	}
}

std::vector<Face*> *ExportObj::CreateTestCube()
{
	std::vector<Face*>* cubeFaces = new std::vector<Face*>();
	Vertex *v000 = new Vertex(0.f, 0.f, 0.f);
	Vertex *v100 = new Vertex(1.f, 0.f, 0.f);
	Vertex *v010 = new Vertex(0.f, 1.f, 0.f);
	Vertex *v110 = new Vertex(1.f, 1.f, 0.f);
	Vertex *v001 = new Vertex(0.f, 0.f, 1.f);
	Vertex *v101 = new Vertex(1.f, 0.f, 1.f);
	Vertex *v011 = new Vertex(0.f, 1.f, 1.f);
	Vertex *v111 = new Vertex(1.f, 1.f, 1.f);
	std::vector<Vertex*>* tempFaceVert = new std::vector<Vertex*>();
	
	//bottom
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v110);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// up
	tempFaceVert->clear();
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v011);
	tempFaceVert->push_back(v101);
	tempFaceVert->push_back(v111);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// front
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v011);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
			
	// back
	tempFaceVert->clear();
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v110);
	tempFaceVert->push_back(v101);
	tempFaceVert->push_back(v111);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// left
	tempFaceVert->clear();
	tempFaceVert->push_back(v000);
	tempFaceVert->push_back(v100);
	tempFaceVert->push_back(v001);
	tempFaceVert->push_back(v101);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	// right
	tempFaceVert->clear();
	tempFaceVert->push_back(v010);
	tempFaceVert->push_back(v110);
	tempFaceVert->push_back(v011);
	tempFaceVert->push_back(v111);
	cubeFaces->push_back(new Face(new std::vector<Vertex*>(*tempFaceVert)));
	
	return cubeFaces;	
}
