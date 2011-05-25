
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
	
	// vertices
	//file << "v " << x << " " << y << " " << z << std::endl;
	
	//faces
	//file << "f " 	<< id1 << "//" << id2 << " "
	//		<< id3 << "//" << id4 << " "
	//		<< id5 << "//" << id6 << std::endl;
	/*std::vector<Vertex*> testVertices;
	testVertices.push_back(new Vertex(0.f, 0.f, 0.f));
	testVertices.push_back(new Vertex(0.f, 1.f, 0.f));
	testVertices.push_back(new Vertex(1.f, 0.f, 0.f));
	testVertices.push_back(new Vertex(1.f, 1.f, 0.f));
	ExportTestCube(testVertices);*/
	
	// test faces cubes
	
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
	
	ExportTestCube(cubeFaces);
	
	file << std::endl;
	
	file.close();
}

/*void ExportObj::ExportVertices(const std::vector<Vertex*>& vertices)
{}*/

void ExportObj::ExportTestCube(const std::vector<Vertex*>& v)
{
	double x = 0.f, y = 0.f;
	Vertex* temp = 0x0;
	double height = 1.f;
	for (int i = 0; i < 4; ++i)
	{
		temp = v[i];
		x = temp->X();
		y = temp->Y();
		file << "v  " << x << "  " << y << "  " << 0.f << std::endl;
		file << "v  " << x << "  " << y << "  " << height << std::endl;
	}
	
	file << "f  " << 1 << "//  " << 7 << "//  " << 5 << "// " << std::endl;
	file << "f  " << 1 << "//  " << 3 << "//  " << 7 << "// " << std::endl;
	file << "f  " << 1 << "//  " << 4 << "//  " << 3 << "// " << std::endl;
	file << "f  " << 1 << "//  " << 2 << "//  " << 4 << "// " << std::endl;
	file << "f  " << 3 << "//  " << 8 << "//  " << 7 << "// " << std::endl;
	file << "f  " << 3 << "//  " << 4 << "//  " << 8 << "// " << std::endl;
	file << "f  " << 5 << "//  " << 7 << "//  " << 8 << "// " << std::endl;
	file << "f  " << 5 << "//  " << 8 << "//  " << 6 << "// " << std::endl;
	file << "f  " << 1 << "//  " << 5 << "//  " << 6 << "// " << std::endl;
	file << "f  " << 1 << "//  " << 6 << "//  " << 2 << "// " << std::endl;
	file << "f  " << 2 << "//  " << 6 << "//  " << 8 << "// " << std::endl;
	file << "f  " << 2 << "//  " << 8 << "//  " << 4 << "// " << std::endl;
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

void ExportObj::ExportFaces(std::vector<Face*>* faces)
{
	// writing vertices
	(void) faces;
	
	
	// writing faces
	
	
}
