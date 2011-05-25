#ifndef BLOCK_H
#define BLOCK_H

#include <vector>
#include "../Geom/Vertex.h"
#include "House.h"
#include "Street.h"

class Block
{
	public:
		Block();
		Block(std::vector<Vertex*>* frontiers);
		~Block();
		
		void Generate();
		
		const std::vector<House*> &GetHouses() const { return *houses; }
		const std::vector<Street*> &GetStreets() const { return *streets; }
	private:
		std::vector<House*>* houses;
		std::vector<Street*>* streets;
		std::vector<Vertex*>* vertices; // frontiers

};

#endif
