class IntRect {
public:
      IntRect() {l = 0; r = 100; b = 0; t = 100;} //constructors
      IntRect(int left, int right, int bottom, int top)
      {l = left; r = right; b = bottom; t = top;}
      void set(int left, int right, int bottom, int top)
      {l = left; r = right; b = bottom; t = top;}
      int getL() {return l;}
      int getR() {return r;}
      int getT() {return t;}
      int getB() {return b;}
      void draw() {glRecti((GLint)l, (GLint)b, (GLint)r, (GLint)t);
                   glFlush();}  //draw this rectangle using OpenGL
private:
      int l,r,b,t;
};
