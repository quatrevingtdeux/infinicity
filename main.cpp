
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Viewer/Viewer.h"
#include "City/City.h"
#include "ExportObj/ExportObj.h"

#define FILENAME "toto.define"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	
	City myCity;
	
	Viewer myViewer(std::string(FILENAME), argc, argv);
	myViewer.Display(&myCity, 512, 512);
	myViewer.Loop();
	return EXIT_SUCCESS;
}
