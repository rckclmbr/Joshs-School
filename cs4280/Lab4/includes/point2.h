#ifndef POINT2_H
#define POINT2_H

#include "header.h"

// Support Classes for Canvas
class Point2   //single point w/ floating point coordinates
{
public:
  Point2();     //contructor 1
  Point2(float xx, float yy);   //constructor 2
  void set(float xx, float yy);
  float getX();
  float getY();
  void draw(void);
private:
  float x, y;
};

#endif
