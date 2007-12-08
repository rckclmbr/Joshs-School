// TODO: Don’t forget to include the header file
// specific to your platform’s graphics layer

#ifndef __linux__
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void);
void display(void);

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("A 3D Object");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
		glColor3f(0.0, 0.0, 1.0);    /* center square */
		glVertex3f(-3.0, -3.0, 0.0);
		glVertex3f(3.0, -3.0, 0.0);
		glVertex3f(3.0, 3.0, 0.0);
		glVertex3f(-3.0, 3.0, 0.0);
	glEnd();
	glBegin(GL_TRIANGLES);
		/* draw four triangles */
		glColor3f(1.0, 0.0, 0.0);  		
		glVertex3f(0.0, 6.5, 0.0);
		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(-3.0, 3.0, 0.0);
		glVertex3f(3.0, 3.0, 0.0);

		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(-3.0, -3.0, 0.0);
		glVertex3f(-3.0, 3.0, 0.0);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(-6.5, 0.0, 0.0);


// TODO: Draw triangle 3 composed of a red vertex at (0, -6.5, 0)
// and two blue vertices of intensity 0.9 at(3, -3, 0) and (-3, -3, 0).
// The triangle should be drawn in a counterclockwise direction.
		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, -3.0, 0.0);
		glVertex3f(-3.0, -3.0, 0.0);
		glColor3f(1.0f, 0.0, 0.0);
		glVertex3f(0.0, -6.5, 0.0);


// TODO: Draw triangle 4 composed of a red vertex at (6.5, 0, 0)
// and two blue vertices of intensity 0.9 at (3, 3, 0) and (3, -3, 0).
// The triangle should be drawn in a counterclockwise direction.
		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, 3.0, 0.0);
		glColor3f(1.0f, 0.0, 0.0);
		glVertex3f(6.5, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, -3.0, 0.0);





	glEnd();
	glutSwapBuffers();
}
