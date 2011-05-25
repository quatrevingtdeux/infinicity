#ifndef VERTEX_H
#define VERTEX_H

#include <cassert>
#include <cmath>
#include <cstdlib>

class Vertex
{
	public :
		Vertex() {}
		Vertex(double a, double b, double c) : x(a), y(b), z(c) {}
		
		double& operator[](int i);
		double operator[](int i) const;
		
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

#endif