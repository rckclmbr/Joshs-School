#include "point2.h"

//constructor 1
Point2::Point2()
{
  x = y = 0.0f;
}

//constructor 2
Point2::Point2(float xx, float yy) 
{
  x=xx; y=yy;
} 

void Point2::set(float xx, float yy) 
{
  x=xx; y=yy;
}

float Point2::getX() 
{
  return x;
}

float Point2::getY() 
{
  return y;
}

void Point2::draw(void)
{
  glBegin(GL_POINTS); //draw this point
    glVertex2f((GLfloat)x, (GLfloat)y);
  glEnd();
}

