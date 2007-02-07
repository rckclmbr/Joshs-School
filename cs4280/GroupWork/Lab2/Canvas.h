//						Learning Team C
//						Members:
//							Lorin Kartchner
//							Todd William Brown
//							Royce Judd
//							Josh Braegger
//							Jeremiah Stephenson
//                      CS 4280 – 7:30 pm
//                      Section 2 Learning Team Assignment
//                      Mr. Rague
//                      Due: 02/07/06
//                      Version: 1.0
// -----------------------------------------------------------------
// This is the header file for the TeamProject2 assignment.  This 
// file contains the class declarations as well as some definitions
// of methods contained in the classes.  The classes Point2, IntRect,
// RealRect, and Canvas were developed using code samples from the 
// text book between pages 101 and 105.  There are additional
// classes contained here that were written for this assignement such
// as Color and Line.  The methods that are not defined in this file
// are defined in Canvas.cpp
// -----------------------------------------------------------------

#include <windows.h>
#include<gl/glut.h>
#include<cmath>
#include<iostream>

using namespace std;

//<<Support Classes for Canvas>>>
class Point2   //single point w/ floating point coordinates
{
public:
	Point2() {x = y = 0.0f;} //constructor 1
	Point2(float xx, float yy) {x=xx; y=yy;} //constructor 2
	void set(float xx, float yy) {x=xx; y=yy;}
	float getX() {return x;}
	float getY() {return y;}
	void draw(void)
	{
		glBegin(GL_POINTS); //draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
		glFlush();
	}
private:
	float x, y;
};

class Color
{
public:
	Color() {red = 0.0; green = 0.0; blue = 0.0;}
	Color(Color *c) {red = c->getRed(); green = c->getGreen(); blue = c->getBlue();}
	Color(float _red, float _green, float _blue) {red = _red; green = _green; blue = _blue;}
	float getRed(void) {return red;}
	float getGreen(void) {return green;}
	float getBlue(void) {return blue;}
	void setColor(float _red, float _green, float _blue) {red = _red; green = _green; blue = _blue;}
	void setColor(Color c) {red = c.getRed(); green = c.getGreen(); blue = c.getBlue();}
private:
	float red, green, blue;
};

class Line
{
public:
	Line() {} 
	Line(Point2 _p1, Point2 _p2, Color _c)		//constructor
	{
		p1.set(_p1.getX(), _p1.getY());			//sets the points
		p2.set(_p2.getX(), _p2.getY());
		c.setColor(_c);							//sets the color
	}
	Line(float x1, float y1, float x2, float y2, Color _c)
	{
		p1.set(x1, y1);
		p2.set(x2, y2);
		c.setColor(_c);
	}
	void setLine(Point2 _p1, Point2 _p2, Color _c)
	{
		p1.set(_p1.getX(), _p1.getY());
		p2.set(_p2.getX(), _p2.getY());
		c.setColor(_c);
	}
	void setPoint1(float x, float y) {p1.set(x, y);}		
	void setPoint1(Point2 p) {p1.set(p.getX(), p.getY());}
	void setPoint2(float x, float y) {p2.set(x, y);}
	void setPoint2(Point2 p) {p2.set(p.getX(), p.getY());}
	void setColor(Color _c) {c.setColor(_c);}
	Point2 getPoint1(void) {return p1;}
	Point2 getPoint2(void) {return p2;}
    float getPoint1X(void) {return p1.getX();}
	float getPoint1Y(void) {return p1.getY();}
	float getPoint2X(void) {return p2.getX();}
	float getPoint2Y(void) {return p2.getY();}
	Color getColor(void)   {return c;}
	float getRed(void)     {return c.getRed();}
	float getGreen(void)   {return c.getGreen();}
	float getBlue(void)    {return c.getBlue();}
private:
	Point2 p1, p2;
	Color c;
};

class IntRect  //aligned rectangle with integer coordinates, used for viewport
{
public:
	IntRect() {l = 0; r=100; b=0; t=100;} //constructors
	IntRect(int left, int right, int bottom, int top)
		{l = left; r=right; b=bottom; t=top;}
	void set(int left, int right, int bottom, int top)
	{
		l=left; r=right; b=bottom; t=top;
	}
	void draw(void); //draw this rectangle using OpenGL
	int getL(void)
	{
		return l;
	}
	int getR(void)
	{
		return r;
	}
	int getT(void)
	{
		return t;
	}
	int getB(void)
	{
		return b;
	}

private:
	int l, r, b, t;
};

class RealRect   //simlar to IntRect but w/ floating points & used for world window
{
public:
	RealRect() {l = 0; r=100; b=0; t=100;} //constructors
	RealRect(float left, float right, float bottom, float top)
		{l = left; r=right; b=bottom; t=top;}
	void set(float left, float right, float bottom, float top)
	{
		l=left; r=right; b=bottom; t=top;
	}
	float getL(void)
	{
		return l;
	}
	float getR(void)
	{
		return r;
	}
	float getT(void)
	{
		return t;
	}
	float getB(void)
	{
		return b;
	}
	void draw(void); //draw this rectangle using OpenGL
private:
	float l, r, b, t;
};


//<<End Support Classes>>>



class Canvas
{
public:
	Canvas(int width, int height, char* windowTitle); //constructor
        void setWindow(float l, float r, float b, float t);
        void setViewport(int l, int r, int b, int t);
        IntRect getViewport(void); //divulge the viewport data
        RealRect getWindow(void); // divulge the window data
        float getWindowAspectRatio(void);
        void clearScreen();
        void setBackgroundColor(float r, float g, float b);
        void setColor(float r, float g, float b);
		Color getColor();
        void lineTo(float x, float y);
        void lineTo(Point2 p);
        void moveTo(float x, float y);
        void moveTo(Point2 p);
		void moveRel(float dx, float dy);
		void lineRel(float dx, float dy);
		void turnTo(float angle);          
		void turn(float angle);
		void forward(float dist, int isVisible);
		void drawRect(float startX, float startY, float xLength, float yLength);
		void drawRect(Point2 p, float xLength, float yLength);
		void nGon(int n, float cx, float cy, float radius, float rotAngle, Point2 *ptr);
		void rosette(int N, Point2 *ptr, int drawNgon);
		void drawLine(Line l);
		
private:
     Point2 CP;         //current position in the world
     IntRect viewport;  //the current window
     RealRect window;   //the current viewport
	 float CD;          //current direction for turtle graphics
	 Color C;           //current drawing color
} ;


