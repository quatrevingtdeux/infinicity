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
		City(double size); // echelle de la zone
		~City();
		
		void Generate();
		std::vector<Face*>* GetFaces() const;
		
		static double HumanSize;
	private:
		void CreateAreas(std::vector<Vertex*> &vertices);
		double size;
		std::vector<Area*>* areas;
		std::vector<Vertex*>* frontiers;
};

#endif


