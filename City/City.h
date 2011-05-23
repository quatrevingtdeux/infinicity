#ifndef CITY_H
#define CITY_H

#include <vector>
#include "Area.h"

class City
{
	public:
		City();
		City(double size, // taille de la zone
		     double humanSize); // echelle de l'homme
		~City();
		
		void Generate();

	private:
		std::vector<Area*> areas;
};

#endif


