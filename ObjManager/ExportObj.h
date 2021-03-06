#ifndef EXPORTOBJ_H
#define EXPORTOBJ_H

#include <fstream>
#include "../City/City.h"
#include "../City/Area.h"
#include "../City/Block.h"
#include "../City/House.h"
#include "../Geom/Face.h"


class ExportObj
{
	public:
		ExportObj(std::string filename) : filename(filename) {}
		~ExportObj() {}
		
		void Export(City* city);
	private:
		std::vector<Face*>* CreateTestCube();
		void ExportTestCube(std::vector<Face*>* faces);
		void ExportFaces(std::vector<Face*>* faces);
		
		std::ofstream file;
		std::string filename;
};

#endif
