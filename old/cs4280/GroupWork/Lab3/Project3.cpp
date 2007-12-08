//						Learning Team C
//						Members:
//							Lorin Kartchner
//							Todd William Brown
//							Royce Judd
//							Josh Braegger
//							Jeremiah Stephenson
//                      CS 4280 – 7:30 pm
//                      Section 3 Learning Team Assignment
//                      Mr. Rague
//                      Due: 02/21/06
//                      Version: 1.0
// -----------------------------------------------------------------
// This programs allows a user to create a convex polygon using the
// mouse.  The user can then create a point on the screen.  The 
// program will run through it's testing algorithums and display
// wether the point is outside or inside the polygon.  As a bonus 
// feature the user can also move the endpoints of the polygon.
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0
//		Date: 02/07/2007
//		Coded algorithum for testing outside or in 
//
//		Team Member: Todd William Brown
//		Version 1.0
//		Date: 02/06/2007
//		Created methods that allows the user to create polygon, move endpoints, and selection location
//
//		Team Member: Royce Judd
//		Version 1.0
//		Date 02/07/2007
//		Commented the code
//
//		Team Member: Josh Braegger
//		Version 1.0
//		Date 02/06/2007
//		Presented code in class
//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
//		Date 02/06/2007
//		Wrote the write up to go with the code

#include "header.h"
#include <iostream>
using namespace std;

void display(void);

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

//class defining a point
class Point2
{
public:
	Point2() {x = y = 0.0f;} 
	Point2(float xx, float yy) {x=xx; y=yy;} 
	void set(float xx, float yy) {x=xx; y=yy;}
	float getX() {return x;}
	float getY() {return y;}
	void draw(void)
	{
		glBegin(GL_POINTS); 
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
		glFlush();
	}

private:
	float x, y;
};

class Vector
{
public:
	Vector() {x = y = 0.0f;} 
	Vector(Point2 pt, Point2 pt2) {
		x = pt.getX() - pt2.getX();
		y = pt.getY() - pt2.getY();	
	}
	float getX() {return x;}
	float getY() {return y;}

	// calculates the length of a vector -- added by Lorin
	float Length(void) { return sqrt(x * x + y * y); }
	
	// calculates the Dot Product of two vectors -- added by Lorin
	float Dot(Vector &vec) { return (x * vec.getX() + y * vec.getY()); }
	
	// normalizes a vector -- added by Lorin 
	void Normalize(void)
	{
		float length = Length();

		x /= length;
		y /= length;
	}
private:
	float x, y;
};

Point2 testPoint; 		// the point in question as to whether inside or outside polygon
Point2 polyPoint[100];  	// the points in the polygon itself (max of 100)
int polyIndex = 0; 		// used for the adjustment of the polygon points
int numPoints = 0; 		// num of points in the polygon array (can be used to loop through populated points)
bool initializeComplete = false;// the polygon has been drawn
bool moveEnabled = false; 	// used for the movement of the polygon points
bool firstPointDrawn = false; 	// makes sure messages are not printed before the very first testPoint is drawn
bool pointInside = false; 	// boolean for inside or outside. Is the ONLY prameter that needs code for the point being inside or outside
#define PI	3.14159  	// defines PI

////////////////////////////////////////////////////////////////
// Function insideOutside: Through various calculations this  //
// function determines whether a point Q is inside or outside //
// of a user defined polygon. -- added by Lorin		      //
////////////////////////////////////////////////////////////////
void insideOutside(Point2 _testPoint, Point2 *_polyPointPtr, int _numPoints)
{
	Point2 Q = _testPoint;		// hold the test point
	Point2 *P = _polyPointPtr;	// pointer to Points list
	Point2 ptNormal[100];		// list of point normals
	GLfloat nX;			// temp x
	GLfloat nY;			// temp y
	float Angle;			// holds the angle of vecQ & vecN
	
	// Find the angles of vectors Q - P & N - P
	for ( int x = 0; x < _numPoints; x++)
	{
		// Used a lot here, let's make them shorter vars
		float pX = P[x].getX();
		float pY = P[x].getY();

		// Calculate normal point
		nX = (pX - P[(x + 1) % _numPoints].getX());
		nY = (pY - P[(x + 1) % _numPoints].getY());

		// fill the ptNormal array with the point normals
		ptNormal[x].set(-(nY) + pX, nX + pY);

		//calculate the Q-P and normal-P  vectors
		Vector vecQ = Vector(Q, P[x]);
		Vector vecN = Vector(ptNormal[x], P[x]);

		//normalize the vectors Q & N
		vecQ.Normalize();
		vecN.Normalize();
		
		// calculate the angle using the Dot product than convert to degrees
		Angle = (acos(vecQ.Dot(vecN))*(180/PI));
		
		// Check angle.  Q is inside if Angle > 90, Outside is Angle < 90
		pointInside = (Angle > 90);
		
		if(!pointInside) break; // break is any angle is outside.
	}

	// refresh display
	glutPostRedisplay();
}

//function that detects mouse movement and moves endpoints
void myMovedMouse(int x, int y)
{
	if (moveEnabled == true)
	{
		polyPoint[polyIndex].set((float) x, (float) (WINDOW_HEIGHT-y));
		glutPostRedisplay();
	}
}

//function that detects mouse clicks and creates the polygon
void myMouseState(int button, int state, int x, int y)
{
	if (initializeComplete == false)
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			polyPoint[numPoints].set((float) x, (float) (WINDOW_HEIGHT-y));
			++numPoints;
		}
		else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN))
			initializeComplete = true;		glutPostRedisplay();
	}
	else
	{
		switch (button)
		{
		case (GLUT_RIGHT_BUTTON):
			if (state == GLUT_DOWN)
			{
				moveEnabled = false;
				for (int index=0; index<numPoints; index++)
				{
					if ((x < ((int)polyPoint[index].getX() + 20)) &&
						(x > ((int)polyPoint[index].getX() - 20)) &&
						(y < (WINDOW_HEIGHT - (int)polyPoint[index].getY() + 20)) &&
						(y > (WINDOW_HEIGHT - (int)polyPoint[index].getY() - 20)))
					{
						moveEnabled = true;
						polyIndex = index;
					}
				}
			}
			else if (state == GLUT_UP)
			{
				moveEnabled = false;
				if (firstPointDrawn == true)
				{
					//pointInside = true; //remove this--for test only
					Point2 *polyPointPtr;
					polyPointPtr = &polyPoint[0];
					insideOutside(testPoint, polyPointPtr, numPoints);
				}
			}
			break;

		case (GLUT_LEFT_BUTTON):
			if (state == GLUT_DOWN)
			{
				//pointInside = false; //remove this--for test only
				Point2 *polyPointPtr;
				polyPointPtr = &polyPoint[0];
				testPoint.set((float) x, (float) (WINDOW_HEIGHT-y));
				firstPointDrawn = true;
				insideOutside(testPoint, polyPointPtr, numPoints);
			}
			break;

		default:
			break;
		}
	}
}

//main function
int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Team C Project 3");

	glClearColor(0.0,0.0,0.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(8);
	glLineWidth(3);
	glutDisplayFunc(display);
	glutMouseFunc(myMouseState);
	glutMotionFunc(myMovedMouse);
	glutMainLoop();
	return 0;
}

//glut display function
void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	// Draw all the points
	glColor3f(1.0, 0.0, 0.0);  
	for (int x=0; x<numPoints; x++)
		polyPoint[x].draw();

	// Draw the polgon
	if (initializeComplete)
	{
		glColor3f(0.0, 0.0, 1.0);
		glBegin(GL_LINE_LOOP);
	for (int x=0; x<numPoints; x++)
			glVertex2f(polyPoint[x].getX(), polyPoint[x].getY());
		glEnd();
	}
	
	// Draw the test point, and the text saying whether it's inside or outside.
	if (firstPointDrawn)
	{
		char inside[] = "The point drawn is INSIDE the polygon.";
		char outside[] = "The point drawn is OUTSIDE the polygon.";

		glColor3f(0.0, 1.0, 0.0);  
		testPoint.draw();

		char* dispText = (pointInside) ? inside : outside;

		glRasterPos2i(100,100);
		for (int x=0; x< strlen(dispText); x++)
			glutBitmapCharacter(GLUT_BITMAP_8_BY_13, dispText[x]);

	}
	glutSwapBuffers();
}
