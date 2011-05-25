#ifndef CITY_H
#define CITY_H

#include <vector>
#include "Area.h"
#include "House.h"
#include "Street.h"
#include "../Geom/Vertex.h"
#include "../Geom/Face.h"

class City
{
	public:
		City();
		City(double size, // taille de la zone
		     double humanSize); // echelle de l'homme
		~City();
		
		void Generate();
		std::vector<Face*>* GetFaces() const;
		
	private:
		double size;
		double humanSize;
		std::vector<Area*>* areas;
		std::vector<Vertex*>* frontiers;
};

#endif


