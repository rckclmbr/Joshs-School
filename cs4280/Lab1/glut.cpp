#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;

#ifndef __linux__
#include <windows.h>
#endif

void init(void);
void display(void);

int main (int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(250, 250);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("My First OpenGL Application");

	init();

	glutDisplayFunc(display);
	glutMainLoop();


	return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0); /* set the background 
	         	                      (clearing) color to
                       	      		      RGBA(0,0,0,0) -- black */
	glColor3f(0.0, 0.0, 1.0);	   /* set the foreground color
					      to blue */
	glMatrixMode(GL_PROJECTION);	   /* Initialize the matrix state */	
	glLoadIdentity();
	glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glRectf(-5.0, 5.0, 5.0, -5.0);
	glFlush();
}
