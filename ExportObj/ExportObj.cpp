
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
	std::vector<Vertex*> testVertices;
	testVertices.push_back(new Vertex(0.f, 0.f, 0.f));
	testVertices.push_back(new Vertex(0.f, 1.f, 0.f));
	testVertices.push_back(new Vertex(1.f, 0.f, 0.f));
	testVertices.push_back(new Vertex(1.f, 1.f, 0.f));
	ExportTestCube(testVertices);
	
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
