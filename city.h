// Changelog 14.02.2001

#ifndef __City__ 
#define __City__

#include "geometry.h"

inline int Intersect(const Vector& a,const Vector& b,const Vector& c,const Vector& d)
{
}
class BlockTriangle:public Triangle {
protected:
public:
  BlockTriangle(const Vector&,const Vector&,const Vector&);
  void Subdivide();
};

class LandTriangle:public Triangle {
protected:
public:
  LandTriangle(const Vector&,const Vector&,const Vector&);
  void Subdivide();
};

class BlockQuad:public Quadrangle {
protected:
public:
  BlockQuad(const Vector&,const Vector&,const Vector&,const Vector&);
  void Subdivide();
};

class LandQuad:public Quadrangle{
protected:
public:
  LandQuad(const Vector&,const Vector&,const Vector&,const Vector&);
  void Subdivide();
};


class City {
private:
public:
  City();
  void Generate();
};

#endif