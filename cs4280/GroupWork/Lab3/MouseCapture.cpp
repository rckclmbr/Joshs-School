#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>

#include"canvas.h"

using namespace std;

Canvas cvs(600,400,"Mouse");

Point2 endpoints[20];
int mouseclick = 0;
void drawpoint(int x,int y)
{
	cvs.setColor(1,0,0);
	glBegin(GL_POINTS);
		glVertex2i(x,y);
	glEnd();
	glFlush();
}
void drawPolygon()
{
	int i=0;
	cvs.setColor(0,0,1);
	glBegin(GL_LINE_LOOP);
		while(endpoints[i].getX() != NULL)
		{
			glVertex2i(endpoints[i].getX(),endpoints[i].getY());
			i++;
		}
	glEnd();
	glFlush();
}

void myMouse(int button, int state, int x, int y)
{
	RealRect window = cvs.getWindow();
	int tempy = window.getT() - window.getB() - y;
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Point2 tempPoint(x,tempy);
		endpoints[mouseclick] = tempPoint;
		drawpoint(x,tempy);
		mouseclick++;
	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		drawPolygon();
	}
}
	

void myDisplay(void)
{
	cvs.clearScreen();
	cvs.setColor(1,0,0);
	glPointSize(5);
	glLineWidth(5);
	glRasterPos2i(100,100);
	char outside[8] = "Outside";
	for(int i=0;i<7;i++)
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13,outside[i]);

	glFlush();
}

void main()
{
	cvs.setBackgroundColor(1,1,1);

	glutDisplayFunc(myDisplay);
	glutMouseFunc(myMouse);
	glutMainLoop();
}
