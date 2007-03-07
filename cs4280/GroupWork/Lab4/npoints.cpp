//						Learning Team C
//						Members:
//							Lorin Kartchner
//							Todd William Brown
//							Royce Judd
//							Josh Braegger
//							Jeremiah Stephenson
//                      CS 4280 – 7:30 pm
//                      Section 4 Learning Team Assignment
//                      Mr. Rague
//                      Due: 03/7/07
//                      Version: 1.0
// -----------------------------------------------------------------
// This program is a demonstration of how three shears produce a 
// rotation.  The program draws a circle and then calculates two
// points on the circle that are equal distance apart.  The program
// also displays the coordinates of these points on the command line
// window.  The user can then use the up arrow key to increase the 
// number of points while the command line window will continually update 
// with the new coordinates.  The user can also use the side arrow
// keys to rotate the points around the circle.  The mouse button
// can be used to change the size of the circle.  The function that
// is used to calculate the points is a modified version provided
// in the text book on page 280.  This function uses the three shear
// method examined in the case study.
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0
//		Date: Wrote the documentation for the project
//
//
//		Team Member: Todd William Brown
//		Version 1.0
//		Date: Completed task number three for the project
//		
//
//		Team Member: Royce Judd
//		Version 1.0
//		Date: Wrote the other program for the project, DrawArc
//		
//
//		Team Member: Josh Braegger
//		Version 1.0
//		Date: Completed task number one and two of the project
//		
//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
//		Date: 3/3/2007
//		Wrote this program for the fourth portion of the group assignment

#include<windows.h>		//compiler directives
#include<iostream>
#include<cmath>
#include <iomanip>
#include<gl/Gl.h>
#include<gl/glut.h>
using namespace std;

const double pi = 3.14159265359;	//definition of pi


class Point2						//point class
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
	}

private:
	float x, y;
};

class Circle				//Circle class
{
private:
	float degree;
	float radius;
public:
	Circle() {degree = 0;radius = 1;}
	Circle(float rs) {radius = rs;}

	void drawCircle(void)
	{
		glBegin(GL_LINE_LOOP);		
 
		for (int i=0; i < 360; i++)
		{
			float degree = i*(pi/180);
			glVertex2f(cos(degree)*radius,sin(degree)*radius);
		}
 
		glEnd();
	}
};

static int num_points = 2;
float radius = 4;			
float rotate = 0;
int windowWidth = 500;
int windowHeight = 500;
GLdouble coor = 5;
Point2 circlePoint[50];

void display(void);
void keyboard(int key, int x, int y);
void reshape(int x, int y);
void drawPoints(Point2 p, double R, double startangle, double sweep);
void myMouse(int, int, int, int);	

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(400,400);
	glutCreateWindow("Circle Points.cpp");
	  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-coor, coor, -coor, coor);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(8);
	glClearColor(1.0,1.0,1.0,0.0);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutMouseFunc(myMouse);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display(void)
{
	Circle circ(radius);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.5, 0.0, 0.0);  

	Point2 p(0,0);					//sets the center of the circle to the points (0,0)

	drawPoints(p, radius, 0, 360);		//draws the points depending on how are specified

	glColor3f(0.0, 0.0, 1.5); 
	glLineWidth(2);
	circ.drawCircle();					//draws the blue circle

	cout << endl << "Circle is showing " << num_points << " points " << endl << endl;

	
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);					//displays the coordinates of all points
	for(int j = 0; j < num_points; j++)
	{
		cout << "Point " << j + 1 << " is [" << setprecision(3) << circlePoint[j].getX() << ", " << setprecision(3) << circlePoint[j].getY() << "]" << endl;
		glVertex2f(circlePoint[j].getX(), circlePoint[j].getY());
		
	}
	glEnd();
	glutSwapBuffers();
}

void reshape(int x,int y)
{
	if(x<y)
	{
		glViewport(0,(y-x)/2,x,x);
	}
	else
	{
		glViewport((x-y)/2,0,y,y);
	}
	windowWidth = x;
	windowHeight = y;
}

void keyboard(int key, int x, int y)
{  
	switch (key)
	{
		case GLUT_KEY_UP:				//if up arrow is pressed
			if(num_points < 50)			//limit of 50 points
			{
				num_points++;			//increases the number of points
				glutPostRedisplay();
			}
			break;

		case GLUT_KEY_DOWN:				//if down arrow is pressed
			if(num_points > 2)			//can only go down to 2 points
			{
				num_points--;			//decreases the number of points
				glutPostRedisplay();
			}
			break;

		case GLUT_KEY_LEFT:				//if the left arrow key is pressed
			if(rotate < 360)
			{
				rotate+=2;					//increases the angle
			}
			else
			{
				rotate = 0;
			}
			glutPostRedisplay();
			break;

		case GLUT_KEY_RIGHT:			//if the right arrow key is pressed
			if(rotate > -360)
			{
				rotate-=2;					//decreases the angle
			}
			else
			{
				rotate = 0;
			}
			glutPostRedisplay();
			break;
	}
}

void drawPoints(Point2 p, double R, double startangle, double sweep)
{
	#define RadPerDeg 0.01745329
	double delang = (RadPerDeg * sweep / num_points);
	double T = tan(delang/2);							//calculates the three shears
	double S = 2*T/(1+T*T);
	double snR = R*sin(RadPerDeg*(startangle + rotate));	
	double csR = R*cos(RadPerDeg*(startangle + rotate));
	
	for(int i = 0; i < num_points; i++)
	{
		snR += T * csR;
		csR -= S * snR;
		snR += T * csR;
		circlePoint[i].set(p.getX() + csR, p.getY() + snR);		//sets the points into the array
		circlePoint[i].draw();									//draws the points
	}
}

void myMouse(int button, int state, int mouseX, int mouseY)
{
	GLfloat flip = windowHeight - mouseY;			//flips the y coordinate
	
	GLfloat x = ((((float)mouseX)/windowWidth)*(coor*2)) - coor;		//converts the x value to the right position in the world window
	GLfloat y = ((flip/windowHeight)*(coor*2)) - coor;				//converts the y value to the right position in the world window
	
	if(button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)			//if left button on mouse is pressed
	{
		radius = sqrt((pow(x,2))+(pow(y,2)));				//changes the radius so the circle will change size

		glutPostRedisplay();			
	}
}