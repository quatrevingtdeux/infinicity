#ifndef HOUSE_H
#define HOUSE_H

#include <vector>
#include "../Geom/Vertex.h"
#include "../Geom/Face.h"

class House
{
	public:
		House();
		House(std::vector<Vertex*>* frontiers);
		~House();
		
		void Build();
		
		std::vector<Face*> &GetFaces() { return *faces;}
	private:
		void CreateCubeField(std::vector<Vertex*>& vect, 
					double base, double height);
		void CreatePyramid(double stepDeep);
		
		void CreateStep(std::vector<Vertex*>& vect, double base, double height);
		
		void CreateWindow(Vertex &vL, Vertex &vR, double base, double height);
		std::vector<Vertex*>* vertices;
		std::vector<Face*>* faces;
};

#endif