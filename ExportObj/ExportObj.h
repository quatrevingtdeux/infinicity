#ifndef EXPORTOBJ_H
#define EXPORTOBJ_H

#include <fstream>
#include "../City/City.h"

class ExportObj
{
	public:
		ExportObj() { filename = "toto.obj";}
		ExportObj(std::string filename) : filename(filename) {}
		~ExportObj() {}
		
		void Export(City* city);
	private:
		std::ofstream file;
		std::string filename;
};

#endif
