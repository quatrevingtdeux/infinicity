#ifndef GEOMOP_H
#define GEOMOP_H

#include <vector>
#include "Vertex.h"

std::vector<Vertex*> &Shrink(std::vector<Vertex*> &vertices, double percentage);

Vertex GravityCenter(std::vector<Vertex*> &vertices);

Vertex GravityCenter(Vertex *vertex1, Vertex *vertex2);

double Surface(std::vector<Vertex*> &vertices);

double Distance(Vertex &v1, Vertex &v2);

std::vector<Vertex*> &ReArrange(std::vector<Vertex*> &vertices);
std::vector<Vertex*> &ReArrangeBugged(std::vector<Vertex*> &vertices);

Vertex *PointOnALine(Vertex &v1, Vertex &v2, double percentageFromV1);

double AngleOfView(Vertex &v0, Vertex &v1, Vertex &v2);

#endif
