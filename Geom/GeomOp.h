#ifndef GEOMOP_H
#define GEOMOP_H

#include <vector>
#include "Vertex.h"

std::vector<Vertex*> &Shrink(std::vector<Vertex*> &vertices, double percentage);

Vertex GravityCenter(std::vector<Vertex*> &vertices);

Vertex GravityCenter(Vertex *vertex1, Vertex *vertex2);

#endif
