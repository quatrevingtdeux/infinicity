#ifndef EXPORTOBJ_H
#define EXPORTOBJ_H

#include <fstream>
#include "../City/City.h"
#include "../City/Area.h"
#include "../City/Block.h"
#include "../City/House.h"


class ExportObj
{
	public:
		ExportObj() { filename = "toto.obj";}
		ExportObj(std::string filename) : filename(filename) {}
		~ExportObj() {}
		
		void Export(City* city);
	private:
		void ExportArea(Area* area);
		void ExportBlock(Block* block);
		void ExportHouse(House* house);
		
		std::ofstream file;
		std::string filename;
};

#endif
