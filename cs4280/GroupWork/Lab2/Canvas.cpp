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
// This file contains most of the method defintions from the classes
// that are defined in Canvas.h.  Most of the definitions were 
// developed using code from the text book between pages 101 and
// 105.  
// -----------------------------------------------------------------


#include <windows.h>
#include<gl/glut.h>
#include<cmath>
#include<iostream>
#include "CANVAS.H"

using namespace std;

//<<moveTo>>
//changes current point
void Canvas:: moveTo(float x, float y)
{
	CP.set(x, y);
}

//<<lineTo>>
//draws a line from current point to new point
void Canvas:: lineTo(float x, float y)
{
	glBegin(GL_LINES);
		glVertex2f((GLfloat) CP.getX(), (GLfloat) CP.getY());
		glVertex2f((GLfloat) x, (GLfloat) y); //draw the line
	glEnd();
	CP.set (x, y); //update current point to new point
	glFlush();
}

//<<setWindow>>
void Canvas:: setWindow (float l, float r, float b, float t)
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D ((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	window.set (l, r, b, t);
}

//<<setViewport>>
void Canvas:: setViewport (int l, int r, int b, int t)
{
	glViewport(l, b, r-l, t-b);
	viewport.set (l, r, b, t);
}

IntRect Canvas:: getViewport(void)
{
	return viewport;
}

RealRect Canvas:: getWindow(void)
{
	return window;
}

void Canvas:: clearScreen(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas:: setBackgroundColor(float r, float g, float b)
{
	glClearColor(r, g, b, 0.0);   //4th variable level of transparency, may need to change 
}

void Canvas:: setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
	C.setColor(r, g, b);
}

Color Canvas::getColor()
{
	return C;
}

void Canvas:: lineTo(Point2 p)
{
	glBegin (GL_LINES);
		glVertex2f((GLfloat) CP.getX(), (GLfloat) CP.getY());
		glVertex2f((GLfloat) p.getX(), (GLfloat) p.getY());
	glEnd();
	CP.set(p.getX(), p.getY());
	glFlush();
}

Canvas:: Canvas(int width, int height, char* windowTitle)
{
	char* argv[1];  //dummy argument list for glutinit()
	char dummyString[8];
	argv[0] = dummyString;  //hook up the pointer
	int argc = 1;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition (20,20);
	glutCreateWindow (windowTitle);
	//setWindow((float)(-1*width)/2, (float)width/2, (float)(-1*height)/2, (float)height/2); // default world window
	//setViewport (0, width, 0, height); //default viewport
	CP.set(0.0f, 0.0f); //initialize the cp to (0,0)
}

void Canvas:: moveTo(Point2 p)  //moves current point CP to point p object 
{
	float x1, y1;
	x1 = p.getX();
	y1 = p.getY();
	CP.set(x1, y1);
}

float Canvas:: getWindowAspectRatio(void)  //calculates aspect ratio of world window
{
	float width, height, aspectRatio;
	width = window.getR() - window.getL();
	height = window.getT() - window.getB();
	aspectRatio = width/height;
	return aspectRatio;
}

void Canvas:: moveRel(float dx, float dy)
{
	CP.set(CP.getX() + dx, CP.getY() + dy);
}

void Canvas:: lineRel(float dx, float dy)
{
	float x = CP.getX() + dx, y = CP.getY() + dy;
	lineTo(x, y);
	CP.set(x, y);
}

void Canvas::turnTo(float angle)
{
	CD = angle;
}

void Canvas::turn(float angle)
{
	CD += angle;
}

void Canvas::forward(float dist, int isVisible)
{
	const float RadPerDeg=0.017453393;
	float x = CP.getX() + dist * cos(RadPerDeg * CD);
	float y = CP.getY() + dist * sin(RadPerDeg * CD);
	if(isVisible)
		lineTo(x, y);
	else
		moveTo(x, y);
}

void Canvas::drawRect(float startX, float startY, float xLength, float yLength)
{
	moveTo(startX, startY);
	glBegin(GL_LINE_LOOP);
		glVertex2f(startX, startY);
		glVertex2f(startX, startY+yLength);
		glVertex2f(startX+xLength, startY+yLength);
		glVertex2f(startX+xLength, startY);
	glEnd();
	glFlush();
}

void Canvas::drawRect(Point2 p, float xLength, float yLength)
{
	moveTo(p.getX(), p.getY());
	glBegin(GL_LINE_LOOP);
		glVertex2f(p.getX(), p.getY());
		glVertex2f(p.getX(), p.getY()+yLength);
		glVertex2f(p.getX()+xLength, p.getY()+yLength);
		glVertex2f(p.getX()+xLength, p.getY());
	glEnd();
	glFlush();
}

void Canvas::nGon(int n, float cx, float cy, float radius, float rotAngle, Point2 *ptr)
{
	if(n < 3) return;
	double angle = rotAngle * 3.14159265 / 180;
	double angleInc = 2 * 3.14159265 / n;
	moveTo(radius * cos(angle) + cx, radius * sin(angle) + cy);
	for(int k=0; k<n; k++)
	{
		angle += angleInc;
		//lineTo(radius * cos(angle) + cx, radius * sin(angle) + cy);
		(ptr+k)->set(radius * cos(angle) + cx, radius * sin(angle) + cy);
		glFlush();
	}
}

void Canvas::rosette(int N, Point2 *ptr, int drawNgon)
{
	switch (drawNgon)
	{
		case 1:
			for(int i=0; i<N-1; i++)
			{
				for(int j=i+1; j<N; j++)
				{
					moveTo((ptr+i)->getX(), (ptr+i)->getY());
					lineTo((ptr+j)->getX(), (ptr+j)->getY());
				}
			}

		default:
			for(int i=0; i<N-1; i++)
			{
				for(int j=i+2; j<N; j++)
				{
					moveTo((ptr+i)->getX(), (ptr+i)->getY());
					if(!((i == 0) && (j == N-1)))
						lineTo((ptr+j)->getX(), (ptr+j)->getY());
				}
			}
			break;
	}
	glFlush();
}

void Canvas::drawLine(Line l)
{
	Color originalColor(C.getRed(), C.getGreen(), C.getBlue());
	setColor(l.getRed(), l.getGreen(),  l.getBlue());
	moveTo(l.getPoint1());
	lineTo(l.getPoint2());
	setColor(originalColor.getRed(), originalColor.getGreen(), originalColor.getBlue());
}

void RealRect::draw()
{
	glBegin(GL_LINE_LOOP);
		glVertex2f(l,t);
		glVertex2f(r,t);
		glVertex2f(r,b);
		glVertex2f(l,b);
	glEnd();
	glFlush();
}


