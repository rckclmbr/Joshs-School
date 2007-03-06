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
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0
//		Date: 
//
//
//		Team Member: Todd William Brown
//		Version 1.0
//		Date: 
//		
//
//		Team Member: Royce Judd
//		Version 1.0
//		Date:
//		
//
//		Team Member: Josh Braegger
//		Version 1.0
//		Date:
//		
//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
//		Date: 3/3/2007
//		Wrote this program for the fourth portion of the group assignment

#include<windows.h>
#include<iostream>
#include<cmath>
#include <iomanip>
#include<gl/Gl.h>
#include<gl/glut.h>
using namespace std;

const double pi = 3.14159265359;


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
	}

private:
	float x, y;
};

class Circle
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
Point2 circlePoint[50];
Circle circ(radius);

void display(void);
void keyboard(int key, int x, int y);
void reshape(int x, int y);
void drawPoints(Point2 p, double R, double startangle, double sweep);

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(400,400);
	glutCreateWindow("Circle Points.cpp");
	  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5, 5, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(8);
	glClearColor(1.0,1.0,1.0,0.0);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(1.5, 0.0, 0.0);  

	Point2 p(0,0);

	drawPoints(p, radius, 0, 360);

	glColor3f(0.0, 0.0, 1.5); 
	glLineWidth(2);
	circ.drawCircle();

	cout << endl << "Circle is showing " << num_points << " points " << endl << endl;

	
	glColor3f(0.0, 1.0, 0.0);
	glLineWidth(1);
	glBegin(GL_LINE_LOOP);
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
		glViewport(0,(y-x)/2,x,x);
	else
		glViewport((x-y)/2,0,y,y);
}

void keyboard(int key, int x, int y)
{  
	switch (key)
	{
		case GLUT_KEY_UP:
			if(num_points < 50)
			{
				num_points++;
				glutPostRedisplay();
			}
			break;

		case GLUT_KEY_DOWN:
			if(num_points > 2)
			{
				num_points--;
				glutPostRedisplay();
			}
			break;

		case GLUT_KEY_LEFT:
			rotate+=2;
			glutPostRedisplay();
			break;

		case GLUT_KEY_RIGHT:
			rotate-=2;
			glutPostRedisplay();
			break;
	}
}

void drawPoints(Point2 p, double R, double startangle, double sweep)
{
	#define RadPerDeg 0.01745329
	double delang = (RadPerDeg * sweep / num_points);
	double T = tan(delang/2);
	double S = 2*T/(1+T*T);
	double snR = R*sin(RadPerDeg*(startangle + rotate));
	double csR = R*cos(RadPerDeg*(startangle + rotate));
	
	for(int i = 0; i < num_points; i++)
	{
		snR += T * csR;
		csR -= S * snR;
		snR += T * csR;
		circlePoint[i].set(p.getX() + csR, p.getY() + snR);
		circlePoint[i].draw();
	}
}