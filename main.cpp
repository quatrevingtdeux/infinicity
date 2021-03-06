
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "define.h"
#include "City/City.h"
#include "ObjManager/ExportObj.h"

int main()
{
	srand(time(NULL));
	
	std::cout << "=== Generation ===" << std::endl;
	
	City myCity;
	myCity.Generate();
	
	std::cout << "=== Export OBJ ===" << std::endl;
	ExportObj exporter(std::string(EXPORT_FILENAME));
	exporter.Export(&myCity);
	
	std::cout << "=== Export OBJ termine ===" << std::endl;
	
	return EXIT_SUCCESS;
}
