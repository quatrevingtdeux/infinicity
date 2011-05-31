
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "define.h"
#include "Viewer/Viewer.h"
#include "City/City.h"
#include "ObjManager/ExportObj.h"

int main(int argc, char* argv[])
{
	(void) argc;
	(void) argv;
	
	srand(time(NULL));
	
	City myCity;
	myCity.Generate();
	
	ExportObj exporter(std::string(EXPORT_FILENAME));
	exporter.Export(&myCity);
	
	//Viewer myViewer(std::string(FILENAME), argc, argv);
	//myViewer.Display(&myCity, 512, 512);
	//myViewer.Loop();
	
	std::string cmd("du -bh "EXPORT_FILENAME);
	system(cmd.c_str());
	return EXIT_SUCCESS;
}
