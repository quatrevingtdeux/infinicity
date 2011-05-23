#ifndef AREA_H
#define AREA_H

#include <vector>
#include "Block.h"

class Area
{
	public:
		Area();
		~Area();
		
		void Subdivide();

	private:
		std::vector<Block*> blocks;
};

#endif
