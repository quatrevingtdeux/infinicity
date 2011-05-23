
#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>

#include "ExportObj.h"

void ExportObj::Export(City* city)
{
	file.open(filename.c_str());
	if (file)
	{
		std::cerr << "Unable to create OBJ file" << std::endl;
		exit(EXIT_FAILURE);
	}
	(void)city;
	
	std::cout << "write in " << filename << std::endl;
	
	file.close();
}