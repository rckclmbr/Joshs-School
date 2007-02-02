//world window rectangle class
class RealRect   
{
public:
  RealRect(); //constructors
  RealRect(float left, float right, float bottom, float top);
  void set(float left, float right, float bottom, float top);
  float getL(void);     //left boundary
  float getR(void);     //right
  float getT(void);
  float getB(void);
  void draw(void); 	//draw this rectangle using OpenGL
private:
  float l, r, b, t;
};

//constructors
RealRect::RealRect() 
{
  l = 0; r=100; b=0; t=100;
}
 
RealRect::RealRect(float left, float right, float bottom, float top)
{
  l = left; r=right; b=bottom; t=top;
}

void RealRect::set(float left, float right, float bottom, float top)
{
  l=left; r=right; b=bottom; t=top;
}

float RealRect::getL(void)      //left boundary
{
  return l;
}

float RealRect::getR(void)      //right
{
  return r;
}

float RealRect::getT(void)
{
  return t;
}

float RealRect::getB(void)
{
  return b;
}

void RealRect::draw(void)
{
  glRectf( l, b, r, t);
}
