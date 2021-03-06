
#include <iostream>
#include <sstream>

#include "ImportObj.h"
#include "../Geom/GeomOp.h"

ImportObj::ImportObj(std::string filename)
{
	this->filename = filename;
	Import();
}

ImportObj::~ImportObj()
{
	faces.clear();	
}

void ImportObj::Import()
{
	file.open(filename.c_str());
	if (file == NULL)
	{
		std::cerr << "Unable to open OBJ file: ";
		std::cerr << filename << std::endl;
		exit(EXIT_FAILURE);
	}
	
	std::string char_line, code;
	
	// read header
	do
	{
		getline(file, char_line);
		
	} while (char_line[0] != 'v');
	
	// --- store vertices
	std::vector<Vertex> vertices;
	double x, y, z;
	do
	{
		std::istringstream line(char_line);
		code = " ";
		line >> code;
		if (code == "v")
		{
			line >> x >> y >> z;
			vertices.push_back(Vertex(x, y, z));
		}
		getline(file, char_line);
		
	} while (char_line[0] != 'f');
	
	// --- push triangular faces
	std::vector<Vertex *> *vert;
	std::string v[4];
	int id, num;
	while (true)
	{
		std::istringstream line(char_line);
		line >> code;
		if (code == "f")
		{
			v[3] = " ";
			line >> v[0] >> v[1] >> v[2] >> v[3];
			vert = new std::vector<Vertex *>();
			
			num = (v[3] != " ") ? 4 : 3;
			for (int i = 0; i < num; i++)
			{
				id = atoi(v[i].substr(0, v[i].find('/')).c_str());
				vert->push_back(new Vertex(vertices[id-1]));
			}
			
			faces.push_back(new Face(vert));
		}
		
		if (file.eof())
		{
			break;
		}
		
		getline(file, char_line);
	}
	
	file.close();
}
