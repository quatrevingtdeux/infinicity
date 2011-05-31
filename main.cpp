
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Viewer/Viewer.h"
#include "City/City.h"
#include "ObjManager/ExportObj.h"

#define FILENAME "obj/test.obj"

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	
	srand(time(NULL));
	
	City myCity;
	myCity.Generate();
	
	ExportObj exporter(std::string(FILENAME));
	exporter.Export(&myCity);
	
	//Viewer myViewer(std::string(FILENAME), argc, argv);
	//myViewer.Display(&myCity, 512, 512);
	//myViewer.Loop();
	
	std::string cmd("du -bh "FILENAME);
	system(cmd.c_str());
	return EXIT_SUCCESS;
}
