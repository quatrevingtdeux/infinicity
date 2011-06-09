
#include <iostream>
#include <fstream>
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
	
	std::cout << "write in " << filename.c_str() << std::endl;
	
	file << "# " << filename.c_str() << std::endl << "# " << std::endl;
	file << std::endl << "g city" << std::endl << std::endl;
	
	ExportFaces(city->GetFaces());
	
	file << std::endl;
	
	file.close();
}


void ExportObj::ExportFaces(std::vector<Face*>* faces)
{
	std::cout << "size:  \t" << faces->size() << " faces" << std::endl;
	long int sum_vert = 0;
	std::vector<Face *>::iterator itf;
	for (itf = faces->begin(); itf != faces->end(); ++itf)
		sum_vert += (*itf)->GetVerticesNumber();
	std::cout << "\t" << sum_vert << " vertices" << std::endl;
	
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
	int next_id = 1, size;
	int id, id1, id2, id3;
	
	for (iteFace = faces->begin(); iteFace != faces->end(); ++iteFace)
	{
		size = (*iteFace)->GetVertices().size();
		if (size == 4)
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
		else if (size ==  3)
		{
			id = next_id;
			file << "f  " << id << "//  " << id+1 << "//  ";
			file << id+2 << "// " << std::endl;
			next_id += 3;
		}
	}
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