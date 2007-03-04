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
		glVertex2f((GLfloat)x, (GLfloat)y);
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
float radius = 1;
Point2 circlePoint[50];
Circle circ(1);

void display(void);
void keyboard(int key, int x, int y);
void reshape(int x, int y);

int main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(400,400);
	glutInitWindowPosition(400,400);
	glutCreateWindow("Circle Points.cpp");
	  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPointSize(8);
	glLineWidth(2);
	glClearColor(1.0,1.0,1.0,0.0);
	glutDisplayFunc(display);
	glutSpecialFunc(keyboard);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void display(void)
{
	double angle;

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);

	glColor3f(1.5, 0.0, 0.0);  

    for(int i = 0; i < num_points; i++)
	{
		angle = i*2*pi/num_points;
	
		GLfloat x = cos(angle)*radius;
		GLfloat y = sin(angle)*radius;

		circlePoint[i].set(x, y);

		circlePoint[i].draw();
    }
	glEnd();

	glColor3f(0.0, 0.0, 1.5);  
	circ.drawCircle();

	cout << endl << "Circle is showing " << num_points << " points " << endl << endl;
	for(int j = 0; j < num_points; j++)
	{
		cout << "Point " << j + 1 << " is [" << circlePoint[j].getX() << ", " << circlePoint[j].getY() << "]" << endl;
	}
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
	}
}