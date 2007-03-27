#ifndef CANVAS_H
#define CANVAS_H

#include "header.h"
#include "realrect.h"
#include "intrect.h"
#include "point2.h"
#include <math.h>

class Canvas
{
public:
	Canvas(int width, int height, char* windowTitle); //constructor
	void setWindow(float l, float r, float b, float t);
	void setViewport(int l, int r, int b, int t);
	IntRect getViewport(void); 		// divulge the viewport data
	RealRect getWindow(void); 		// divulge the window data
	float getWindowAspectRatio(void);
	void clearScreen();
	void setBackgroundColor(float r, float g, float b);
	void setColor(float r, float g, float b);
	void lineTo(float x, float y);
	void lineTo(Point2 p);
	void moveTo(float x, float y);
	void moveTo(Point2 p);
	void moveRel(float dx, float dy);
	void lineRel(float dx, float dy);
	float getCD(void) { return CD; }	// get the current direction
	Point2 getCP(void) { return CP; }
	
	// Turtle methods
	void turnTo(float angle);
	void turn(float angle);
	void forward(float dist, int isVisible);

private:
	float CD;
	Point2 CP;         //current position in the world
	IntRect viewport;  //the current window
	RealRect window;   //the current viewport
};

#endif
