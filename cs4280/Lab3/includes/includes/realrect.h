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

//constructors
RealRect::RealRect()  { l = 0; r=100; b=0; t=100; }
 
RealRect::RealRect(float left, float right, float bottom, float top)
{ l = left; r=right; b=bottom; t=top; }

void RealRect::set(float left, float right, float bottom, float top)
{ l=left; r=right; b=bottom; t=top; }
