// Vector  
// Changelog 02.02.07

#ifndef __Geometry__
#define __Geometry__

#include "vector.h"

class Triangle{
protected:
	Vector p[3];
public:
	Triangle() {}
	Triangle(const Vector&,const Vector&,const Vector&);
	Triangle Shrink(const double&,const double&,const double&);
	double Area() const;
	inline Vector operator[](int i) const { return p[i]; }
};

//! \brief Compute the area of a triangle
inline double Triangle::Area() const
{
	return Norm((p[1]-p[0])/(p[2]-p[0]))/2.0;
}

class Quadrangle
{
protected:
	Vector p[4];
public:
	Quadrangle() {}
	Quadrangle(const Vector&,const Vector&,const Vector&,const Vector&);
	Quadrangle Shrink(const double&,const double&,const double&,const double&);
	double Area() const;
	inline Vector operator[](int i) const { return p[i]; }
};

//! \brief Compute the area of a quadrangle
inline double Quadrangle::Area() const
{
	return Norm((p[1]-p[0])/(p[2]-p[0]))+Norm((p[2]-p[0])/(p[3]-p[0]));
}

#endif