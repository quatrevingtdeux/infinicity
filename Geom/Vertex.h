#ifndef VERTEX_H
#define VERTEX_H

#include <cassert>
#include <cmath>
#include <cstdlib>

class Vertex
{
	public :
		Vertex() {}
		Vertex(const double &a, const double &b, const double &c) 
		: x(a), y(b), z(c) {}
		
		double& operator[](int i) {
				assert(0 <= i && i < 3);
				if (i == 0)		return x;
				else if (i == 1)	return y;
				else			return z;
			}

		const double operator[](int i) const { //TODO  cette ligne génère 3 lignes, à corriger
				assert(0 <= i && i < 3);
				if (i == 0)		return x;
				else if (i == 1)	return y;
				else			return z;
			}
		
		double X() const { return x; }
		double Y() const { return y; }
		double Z() const { return z; }
		
		Vertex operator+() const;
		Vertex operator-() const;
		
		Vertex& operator+= (const Vertex&);
		Vertex& operator-= (const Vertex&);
		Vertex& operator*= (const Vertex&);
		Vertex& operator/= (const Vertex&);
		Vertex& operator*= (double);
		Vertex& operator/= (double);
		
		
		friend Vertex operator+ (const Vertex&, const Vertex&);
		friend Vertex operator- (const Vertex&, const Vertex&);
		friend double operator* (const Vertex&, const Vertex&);
		friend Vertex operator* (const Vertex&, double);
		friend Vertex operator* (double, const Vertex&);
		friend Vertex operator/ (const Vertex&, double);

		friend Vertex operator/ (const Vertex&, const Vertex&);

		friend int operator==(const Vertex&,const Vertex&);
		friend int operator!=(const Vertex&,const Vertex&);
		friend int operator<(const Vertex&,const Vertex&);
		friend int operator>(const Vertex&,const Vertex&);
		friend Vertex min(const Vertex&,const Vertex&);
		friend Vertex max(const Vertex&,const Vertex&);

		friend Vertex Orthogonal(const Vertex&);

		// Norm
		friend double Norm(const Vertex&);
		friend Vertex Normalized(const Vertex&);

		friend Vertex Random();
	
	protected:
		double x;
		double y;
		double z;
	
};

inline Vertex Random()
{
	double x = rand()%1001/1000.0;
	double y = rand()%1001/1000.0;
	double z = rand()%1001/1000.0;
	return Vertex(x, y, z);
}

inline Vertex Vertex::operator+ () const
{
	return *this;
}

inline Vertex Vertex::operator- () const
{
	return Vertex(-x, -y, -z);
}

inline Vertex& Vertex::operator+= (const Vertex& u)
{
	x += u.x;
	y += u.y;
	z += u.z;
	return *this;
}

inline Vertex& Vertex::operator-= (const Vertex& u)
{
	x -= u.x;
	y -= u.y;
	z -= u.z;
	return *this;
}

inline Vertex& Vertex::operator*= (double a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}

inline Vertex& Vertex::operator/= (double a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline Vertex& Vertex::operator*= (const Vertex& u)
{
	x *= u.x;
	y *= u.y;
	z *= u.z;
	return *this;
}

inline Vertex& Vertex::operator/= (const Vertex& u)
{
	x /= u.x;
	y /= u.y;
	z /= u.z;
	return *this;
}

inline Vertex operator+ (const Vertex& u, const Vertex& v)
{
	return Vertex(u.x + v.x, u.y + v.y, u.z + v.z);
}

inline Vertex operator- (const Vertex& u, const Vertex& v)
{
	return Vertex(u.x - v.x, u.y - v.y, u.z - v.z);
}

inline double operator* (const Vertex& u, const Vertex& v)
{
	return (u.x*v.x + u.y*v.y + u.z*v.z);
}

inline Vertex operator* (const Vertex& u,double a)
{
	return Vertex(u.x*a, u.y*a, u.z*a);
}

inline Vertex operator* (double a, const Vertex& v)
{
	return v*a;
}

inline Vertex operator/ (const Vertex& u, const Vertex& v)
{
	return Vertex(u.y*v.z - u.z*v.y, u.z*v.x - u.x*v.z, u.x*v.y - u.y*v.x);
}

inline Vertex operator/ (const Vertex& u, double a)
{
	return Vertex(u.x/a, u.y/a, u.z/a);
}

inline int operator== (const Vertex& u,const Vertex& v)
{
	return ((u.x == v.x) && (u.y == v.y) && (u.z == v.z));
}

inline int operator!= (const Vertex& u,const Vertex& v)
{
	return (!(u==v));
}

inline double Norm(const Vertex& u)
{
	return sqrt(u.x*u.x + u.y*u.y + u.z*u.z);
}

inline Vertex Normalized(const Vertex& u)
{
	return u/Norm(u);
}

inline int operator<(const Vertex& a,const Vertex& b)
{
	return ((a.x < b.x) && (a.y < b.y) && (a.z < b.z));
}

inline int operator>(const Vertex& a,const Vertex& b)
{
	return ((a.x > b.x) && (a.y > b.y) && (a.z > b.z));
}

inline Vertex min(const Vertex& a,const Vertex& b)
{
	double x = (a[0] < b[0]) ? a[0] : b[0];
	double y = (a[1] < b[1]) ? a[1] : b[1];
	double z = (a[2] < b[2]) ? a[2] : b[2];
	return Vertex(x, y, z);
}

inline Vertex max(const Vertex& a,const Vertex& b)
{
	double x = (a[0] > b[0]) ? a[0] : b[0];
	double y = (a[1] > b[1]) ? a[1] : b[1];
	double z = (a[2] > b[2]) ? a[2] : b[2];
	return Vertex(x, y, z);
}

inline Vertex Orthogonal(const Vertex& u)
{  
	Vertex a = Vertex(fabs(u[0]), fabs(u[1]), fabs(u[2]));
	int i = 0;
	int j = 1;
	if (a[0] > a[1])
	{
		if (a[2] > a[1])
			j = 2;
	}
	else
	{
		i = 1;
		j = 2;
		if (a[0] > a[2])
			j = 0;
	}
	a = Vertex(0.f, 0.f, 0.f);
	a[i] = u[j];
	a[j] = -u[i];
	
	return a;
}

#endif