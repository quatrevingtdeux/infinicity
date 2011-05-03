#include "shape.h"
#include "city.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <math.h>

// > 1.f
#define SCALE_DIAMETRE 2.f
// < 1.f
#define POURCENTAGE_DISTANCE 0.f

// -BLOCK----------------------------------------------------------------------
/*!
\brief Create a triangular block.
\param a,b,c End vertices of the block.
*/
BlockTriangle::BlockTriangle(const Vector& a,const Vector& b,const Vector& c):Triangle(a,b,c)
{
}

/*!
\brief Create a quadrangular block.
\param a,b,c,d End vertices of the parcel.
*/
BlockQuad::BlockQuad(const Vector& a, const Vector& b,
				 const Vector& c, const Vector& d) : Quadrangle(a, b, c, d)
{}

// -LAND-----------------------------------------------------------------------



/*!
 \ *brief Create a triangular parcel of land.
 \param a,b,c End vertices of the parcel.
 */
LandTriangle::LandTriangle(const Vector& a,const Vector& b,const Vector& c):Triangle(a,b,c)
{
}

/*
 \ *brief Subdivide a triangular land parcel. 
 */
void LandTriangle::Subdivide()
{
	// Area
	double area=Area();
	
	// Check if minimal area : in this case stop 
	// land use subdivision and start base building generation
	if (area<20) 
	{
		Triangle t=Triangle(p[0],p[1],p[2]).Shrink(0.25,0.25,0.25);
		PrismTriangle(t,0.5*(1+rand()%5)).Render(); 
	}
	// Subdivide land use
	else
	{
		// Compute index of smallest edge
		double ab=Norm(p[1]-p[0]);
		double bc=Norm(p[2]-p[1]);
		double ca=Norm(p[0]-p[2]);
		
		if ((ab<ca)&&(ab<bc))
		{
			LandTriangle(p[2],(p[2]+p[0])/2.0,(p[1]+p[2])/2.0).Subdivide();;
			LandQuad((p[2]+p[0])/2.0,p[0],p[1],(p[1]+p[2])/2.0).Subdivide();
		}
		else if ((bc<ab)&&(bc<ca))
		{
			LandTriangle(p[0],(p[0]+p[1])/2.0,(p[0]+p[2])/2.0).Subdivide();;
			LandQuad((p[0]+p[1])/2.0,p[1],p[2],(p[0]+p[2])/2.0).Subdivide();
		}
		else
		{
			LandTriangle(p[1],(p[1]+p[2])/2.0,(p[0]+p[1])/2.0).Subdivide();;
			LandQuad((p[1]+p[2])/2.0,p[2],p[0],(p[0]+p[1])/2.0).Subdivide();
		}
	}
}

/*!
\brief Create a quadrangular parcel of land.
\param a,b,c,d End vertices of the parcel.
*/
LandQuad::LandQuad(const Vector& a, const Vector& b, 
			    const Vector& c, const Vector& d)
: Quadrangle(a, b, c, d)
{
}

Vector gimmeAPoint(const Vector& a, const Vector& b)
{
		
	double x = a[0]+rand()%(int)(b[0]-a[0]);std::cout << "kikoo:" << std::endl;
	double coefDir;
	double y ;
	if (b[0]-a[0] == 0)
	{
		y = a[1]+rand()%(int)(b[1]-a[1]+1);
	}
	else
	{
		coefDir = (b[1]-a[1])/(b[0]-a[0]);
		y = x*coefDir + (a[1]-coefDir*a[0]);
	}
	double z = 0;
	// TODO générique
		std::cout << "cd:" << coefDir << std::endl;
	return Vector(x,y,z);
}

void DonnerPoint(Vector& point, const Vector& a, const Vector& b, double pourcentage)
{
	double rayon;
	point = a + (b-a)/2.f;
	rayon = abs(pourcentage/2 * (a[0]-b[0]));
	point[0] = point[0] + rand()%(int)(2*rayon+1) - rayon;
	rayon = abs(pourcentage/2 * (a[1]-b[1]));
	point[1] = point[1] + rand()%(int)(2*rayon+1) - rayon;
	rayon = abs(pourcentage/2 * (a[2]-b[2]));
	point[2] = point[2] + rand()%(int)(2*rayon+1) - rayon;
}

/*
\brief Subdivide a quadrangular land parcel. 
*/
void LandQuad::Subdivide()
{
	static double height = 1;
	//	height+=0.1;
	double area=Area();
	//std::cout << "area:" << area << std::endl;

	//if (area<10)
	//if (area<100) // multicentre
	if (area < 100) // un centre
	{
		//std::cout << "-- Rendu -- " << area << std::endl;
		Quadrangle q=Quadrangle(p[0],p[1],p[2],p[3]).Shrink(0.25,0.25,0.25,0.25);
		//PrismQuad(q,0.5*(1+rand()%5)).Render(); 
		PrismQuad(q,height).Render(); 
	}
	else
	{

		Vector mid   = p[0]+(p[2]-p[0])/2;
		double diametre;
		diametre = (p[1][0]-p[0][0])/SCALE_DIAMETRE;
		mid[0] += rand()%(int)diametre - diametre/2.f;
		diametre = (p[2][1]-p[1][1])/SCALE_DIAMETRE;
		mid[1] += rand()%(int)diametre - diametre/2.f;
		
		// pour avoir les milieux des bords
		Vector mid01 = p[0]+(p[1]-p[0])/2;
		//mid01[0] = mid[0];
		Vector mid12 = p[1]+(p[2]-p[1])/2;
		//mid12[1] = mid[1];
		Vector mid23 = p[2]+(p[3]-p[2])/2;
		//mid23[0] = mid[0];
		Vector mid03 = p[0]+(p[3]-p[0])/2;
		//mid03[1] = mid[1];
		
		DonnerPoint(mid01, p[0], p[1], POURCENTAGE_DISTANCE);
		DonnerPoint(mid12, p[1], p[2], POURCENTAGE_DISTANCE);
		DonnerPoint(mid23, p[2], p[3], POURCENTAGE_DISTANCE);
		DonnerPoint(mid03, p[0], p[3], POURCENTAGE_DISTANCE);
		
		if (-20.0 > p[0][0] || p[0][0] > 20.0
			|| -20.0 > p[0][1] || p[0][1] > 20.0)
			std::cout << "WARNING ! p[0] : x" << p[0][0] << " y" << p[0][1] << std::endl;
		
		if (-20.0 > p[1][0] || p[1][0] > 20.0
			|| -20.0 > p[1][1] || p[1][1] > 20.0)
			std::cout << "WARNING ! p[1] : x" << p[1][0] << " y" << p[1][1] << std::endl;
		
		if (-20.0 > p[2][0] || p[2][0] > 20.0
			|| -20.0 > p[2][1] || p[2][1] > 20.0)
			std::cout << "WARNING ! p[2] : x" << p[2][0] << " y" << p[2][1] << std::endl;
		
		if (-20.0 > p[3][0] || p[3][0] > 20.0
			|| -20.0 > p[3][1] || p[3][1] > 20.0)
			std::cout << "WARNING ! p[3] : x" << p[3][0] << " y" << p[3][1] << std::endl;
		
		if (-20.0 > mid[0] || mid[0] > 20.0
			|| -20.0 > mid[1] || mid[1] > 20.0)
			std::cout << "WARNING ! mid : x" << mid[0] << " y" << mid[1] << std::endl;
		
		if (-20.0 > mid01[0] || mid01[0] > 20.0
			|| -20.0 > mid01[1] || mid01[1] > 20.0)
			std::cout << "WARNING ! mid01 : x" << mid01[0] << " y" << mid01[1] << std::endl;
				
		if (-20.0 > mid12[0] || mid12[0] > 20.0
			|| -20.0 > mid12[1] || mid12[1] > 20.0)
			std::cout << "WARNING ! mid12 : x" << mid12[0] << " y" << mid12[1] << std::endl;
				
		if (-20.0 > mid23[0] || mid23[0] > 20.0
			|| -20.0 > mid23[1] || mid23[1] > 20.0)
			std::cout << "WARNING ! mid23 : x" << mid23[0] << " y" << mid23[1] << std::endl;
				
		if (-20.0 > mid03[0] || mid03[0] > 20.0
			|| -20.0 > mid03[1] || mid03[1] > 20.0)
			std::cout << "WARNING ! mid03 : x" << mid03[0] << " y" << mid03[1] << std::endl;
		
		
		LandQuad(p[0], mid01, mid, mid03).Subdivide();
		LandQuad(mid01, p[1], mid12, mid).Subdivide();
		LandQuad(mid, mid12, p[2], mid23).Subdivide();
		LandQuad(mid03, mid, mid23, p[3]).Subdivide();
	}
}

// -CITY-----------------------------------------------------------------------

/*!
\brief Constructor of a city
*/
City::City() 
{}

/*!
\brief Generate a city from an initial land triangle.
*/
void City::Generate()
{
	LandQuad(Vector(-20,-20,0),Vector(20,-20,0),Vector(20,20,0),
		    Vector(-20,20,0)).Subdivide();
}

