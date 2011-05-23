
#include <iostream>
#include <cstdlib>
#include <ctime>

#include "Viewer/Viewer.h"
#include "City/City.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	
	City myCity;
	
	Viewer myViewer(argc, argv);
	myViewer.Display(&myCity, 512, 512);
	myViewer.Loop();
	
	return EXIT_SUCCESS;
}
