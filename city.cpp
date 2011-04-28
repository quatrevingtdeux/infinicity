#include "shape.h"
#include "city.h"
#include <vector>
#include <time.h>
#include <iostream>

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

/*
\brief Subdivide a quadrangular land parcel. 
*/
void LandQuad::Subdivide()
{
// 	// Area
// 	double area=Area();
// 
// 	// Check if minimal area : in this case stop 
// 	// land use subdivision and start base building generation
// 	if (area<30)  
// 	{
// 		//Quadrangle q = Quadrangle(p[0], p[1], p[2], p[3])
// 		//						.Shrink(0.25, 0.25, 0.25, 0.25);
// 		static double sh=0.25;
// 		//sh+=0.001;
// 		Quadrangle q = Quadrangle(p[0], p[1], p[2], p[3]).Shrink(sh,sh,sh,sh);
// 		//PrismQuad(q, 0.5*(1+rand()%5)).Render();
// 		PrismQuad(q, 5).Render(); 
// 	}
// 	// Land use subdivison
// 	else
// 	{
// 		/*srand(time(NULL));
// 		if (area > 30)
// 		{
// 			Vector real_center(p[0][0]+(p[2][0]-p[0][0])/2,
// 						    p[0][1]+(p[2][1]-p[0][1])/2,0);
// 			
// 			double minx = p[0][0], maxx = p[2][0];
// 			double miny = p[0][1], maxy = p[2][1];
// 			double largeur = maxx -minx;
// 			double thres = 0.1*largeur;
// 			double rand_x = minx + thres + (rand()%(int)(largeur-2*thres));
// 			double rand_y = miny + thres + (rand()%(int)(largeur-2*thres));
// 			/// TODO : passer en valeurs flottantes !
// 			
// 			Vector city_center(rand_x,rand_y,0);
// 			
// 			
// 			std::cout << thres << std::endl;
// 			std::cout << city_center[0] << " " << city_center[1] << std::endl;
// 			std::vector<Vector> points;
// 			
// 			for (int i = 0; i < 4; ++i)
// 			{
// 				int nb_points = rand()%3;
// 				points.push_back(p[i%4]);
// 				while (nb_points-- > 0)
// 				{
// 					std::cout << (i+1)%4 << " " << p[i%4][0] << std::endl;
// 					points.push_back(gimmeAPoint(p[i%4],p[(i+1)%4]));
// 				}
// 				points.push_back(p[(i+1)%4]);
// 			}
// 			
// 			
// 			
// 			std::vector<Vector>::iterator ite, ite2 = points.begin();
// 			ite2++;
// 			for (ite = points.begin(); ite != points.end(); ++ite)
// 			{
// 				if (ite2 == points.end())
// 					ite = points.begin();
// 				std::cout << (*ite)[0] << " " << (*ite)[1] << std::endl;
// 				LandQuad(*ite, *ite2, real_center, real_center)
// 								.Subdivide();
// 				ite2++;
// 			}
// 			
// 		}*/

// 	}
	double area=Area();
	std::cout << "area:" << area << std::endl;

	//if (area<10)
	if (area<3200)
	{
		Quadrangle q=Quadrangle(p[0],p[1],p[2],p[3]).Shrink(0.25,0.25,0.25,0.25);
		//PrismQuad(q,0.5*(1+rand()%5)).Render(); 
		PrismQuad(q,5).Render(); 
	}
	else
	{
// 		LandTriangle(p[0],p[1],p[2]).Subdivide();
// 		LandTriangle(p[0],p[2],p[3]).Subdivide();
		srand(time(NULL));

		Vector mid   = p[0]+(p[2]-p[0])/(2+area*(rand()%100-50)/100000);
		Vector mid01 = p[0]+(p[1]-p[0])/2;
		mid01[0] = mid[0];
		Vector mid12 = p[1]+(p[2]-p[1])/2;
		mid12[1] = mid[1];
		Vector mid23 = p[2]+(p[3]-p[2])/2;
		mid23[0] = mid[0];
		Vector mid03 = p[0]+(p[3]-p[0])/2;
		mid03[1] = mid[1];
		
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

