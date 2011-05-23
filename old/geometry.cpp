#include <iostream>

#include "geometry.h"

/*!
\class Triangle geometry.h
\brief This class implements a simple triangle.
*/

/*!
\brief Constructor.
*/
Triangle::Triangle(const Vector& a,const Vector& b,const Vector& c)
{
  p[0]=a;
  p[1]=b;
  p[2]=c;
}

Vector Intersection(const Vector& a, const Vector& b, const Vector& c, const Vector& d) 
{ 
  double e = (a[0] - b[0]) * (c[1] - d[1]) - (a[1] - b[1]) * (c[0] - d[0]); 

  double u = (a[0]*b[1] - a[1]*b[0]);
  double v = (c[0]*d[1] - c[1]*d[0]); 

  double x = ( u * (c[0] - d[0]) - (a[0] - b[0]) * v ) / e; 
  double y = ( u * (c[1] - d[1]) - (a[1] - b[1]) * v ) / e; 

  return Vector(x,y,0.0);
}

/*!
\brief Shrinks the triangle by a given orthogonal offset for every edge.
*/
Triangle Triangle::Shrink(const double& ab,const double& bc, const double& ca)
{
  Vector sa = p[0]-Normalized((p[1]-p[0])/Vector(0,0,1))*ab;
  Vector sb = p[1]-Normalized((p[2]-p[1])/Vector(0,0,1))*bc;
  Vector sc = p[2]-Normalized((p[0]-p[2])/Vector(0,0,1))*ca;

  return Triangle(
    Intersection(sa,sa+(p[1]-p[0]),sb,sb+(p[2]-p[1])),
    Intersection(sb,sb+(p[2]-p[1]),sc,sc+(p[0]-p[2])),
    Intersection(sc,sc+(p[0]-p[2]),sa,sa+(p[1]-p[0])));
}


/*!
\class Quadrangle geometry.h
\brief This class implements a simple quadrangle with several useful geometric functions.
*/

/*!
\brief Constructor.
*/
Quadrangle::Quadrangle(const Vector& a,const Vector& b,const Vector& c,const Vector& d)
{
  p[0]=a;
  p[1]=b;
  p[2]=c;
  p[3]=d;
}

/*!
\brief Shrinks the quadrangle by a given orthogonal offset for every edge.
*/
Quadrangle Quadrangle::Shrink(const double& ab,const double& bc, const double& cd, const double& da)
{
  Vector sa = p[0]-Normalized((p[1]-p[0])/Vector(0,0,1))*ab;
  Vector sb = p[1]-Normalized((p[2]-p[1])/Vector(0,0,1))*bc;
  Vector sc = p[2]-Normalized((p[3]-p[2])/Vector(0,0,1))*cd;
  Vector sd = p[3]-Normalized((p[0]-p[3])/Vector(0,0,1))*da;

  return Quadrangle(
    Intersection(sa,sa+(p[1]-p[0]),sb,sb+(p[2]-p[1])),
    Intersection(sb,sb+(p[2]-p[1]),sc,sc+(p[3]-p[2])),
    Intersection(sc,sc+(p[3]-p[2]),sd,sd+(p[0]-p[3])),
    Intersection(sd,sd+(p[0]-p[3]),sa,sa+(p[1]-p[0])));
}
