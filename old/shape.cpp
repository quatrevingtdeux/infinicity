#include "shape.h"

using namespace std;
#include <GL/glew.h>
#include <GL/glut.h>
#include <GL/gl.h>										
#include <GL/glu.h>


/*!
\class PrismTriangle shape.h
This class imprements a prism based on a triangle base.
*/

/*!
\brief Creates a prism with a triangle base.
*/
PrismTriangle::PrismTriangle(const Vector& a,const Vector& b,const Vector& c,const double& h):Triangle(a,b,c)
{
  PrismTriangle::h=h;
}

/*!
\brief Creates a prism with a triangle base.
*/
PrismTriangle::PrismTriangle(const Triangle& t,const double& h)
{
  p[0]=t[0];
  p[1]=t[1];
  p[2]=t[2];
  PrismTriangle::h=h;
}
/*!
\brief Renders a triangular prism.
\note This function ommits the lower face of the prism.
*/
void PrismTriangle::Render()
{
  glBegin(GL_TRIANGLES);

  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[1][0],p[1][1],p[1][2]+h);
  glVertex3f(p[2][0],p[2][1],p[2][2]+h);

  glEnd();

  // Other faces
  glBegin(GL_QUADS);

  for (int i=0;i<3;i++)
  {
    int j=(i+1)%3;
    Vector n=(p[j]-p[i])/Vector(0,0,1);
    n/=Norm(n);
    glNormal3f(n[0],n[1],0.0f);
    glVertex3f(p[i][0],p[i][1],p[i][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]+h);
    glVertex3f(p[i][0],p[i][1],p[i][2]+h);
  }

  glEnd();
}

/*!
\class PrismQuad shape.h
\brief This class Implements a prism based on a quadrangle.
*/

/*!
\brief Creates a prism with a quadrangle base.
*/
PrismQuad::PrismQuad(const Vector& a,const Vector& b,const Vector& c,const Vector& d,const double& h):Quadrangle(a,b,c,d)
{
  PrismQuad::h=h;
}

/*!
\brief Creates a prism with a quadrangle base.
*/
PrismQuad::PrismQuad(const Quadrangle& q,const double& h)
{
  p[0]=q[0];
  p[1]=q[1];
  p[2]=q[2];
  p[3]=q[3];
  PrismQuad::h=h;
}

/*!
\brief Renders a quadrilateral prism.
\note This function ommits the lower face of the prism.
*/
void PrismQuad::Render()
{
  glBegin(GL_QUADS);

  // Face z=+1
  glNormal3f( 0.0f, 0.0f,1.0f);
  glVertex3f(p[0][0],p[0][1],p[0][2]+h);
  glVertex3f(p[1][0],p[1][1],p[1][2]+h);
  glVertex3f(p[2][0],p[2][1],p[2][2]+h);
  glVertex3f(p[3][0],p[3][1],p[3][2]+h);

  glEnd();

  // Other faces
  glBegin(GL_QUADS);

  for (int i=0;i<4;i++)
  {
    int j=(i+1)%4;
    Vector n=(p[j]-p[i])/Vector(0,0,1);
    n/=Norm(n);
    glNormal3f(n[0],n[1],0.0f);
    glVertex3f(p[i][0],p[i][1],p[i][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]);
    glVertex3f(p[j][0],p[j][1],p[j][2]+h);
    glVertex3f(p[i][0],p[i][1],p[i][2]+h);
  }

  glEnd();
}



