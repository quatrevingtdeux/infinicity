
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
	
	file << std::endl;
	
	file.close();
}

void ExportObj::ExportArea(Area* area)
{
	
}

void ExportObj::ExportBlock(Block* block)
{
	
}

void ExportObj::ExportHouse(House* house)
{
	
}