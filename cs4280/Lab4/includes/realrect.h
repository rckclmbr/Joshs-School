#ifndef REALRECT_H
#define REALRECT_H

#include "header.h"

//world window rectangle class
class RealRect   
{
public:
  RealRect(); //constructors
  RealRect(float left, float right, float bottom, float top);
  void set(float left, float right, float bottom, float top);
  float getL() {return l;}
  float getR() {return r;}
  float getT() {return t;}
  float getB() {return b;}
  void draw() {glRectf((GLfloat)l, (GLfloat)b, (GLfloat)r, (GLfloat)t);
                   glFlush();}  //draw this rectangle using OpenGL
private:
  float l, r, b, t;
};

#endif
