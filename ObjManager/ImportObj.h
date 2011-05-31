#ifndef IMPORTOBJ_H
#define IMPORTOBJ_H

#include <string>
#include <vector>
#include <fstream>

#include "../Geom/Face.h"

class ImportObj
{
	public:
		ImportObj(std::string filename);
		~ImportObj();
		
		std::vector<Face*> &GetFaces() { return faces; }
	private:
		void Import();
		std::vector<Face*> faces;
		
		std::ifstream file;
		std::string filename;
};

#endif