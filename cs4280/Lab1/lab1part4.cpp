#ifndef __linux__
#include <windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void init(void);
void display(void);
void keyboard(unsigned char key, int x, int y);

int main (int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("A 3D Object");
	init();
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-15.0, 15.0, -15.0, 15.0, -15.0, 15.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, -3.0, 0.0);
		glVertex3f(-3.0, -3.0, 0.0);
		glColor3f(1.0f, 0.0, 0.0);
		glVertex3f(0.0, -6.5, 0.0);

		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, 3.0, 0.0);
		glColor3f(1.0f, 0.0, 0.0);
		glVertex3f(6.5, 0.0, 0.0);
		glColor3f(0.0, 0.0, 0.9f);
		glVertex3f(3.0, -3.0, 0.0);
	glEnd();
	glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)
{
	/* this is the keyboard event handler
	   the x and y parameters are the mouse 
	   coordinates when the key was struck */
	switch (key)
	{
	case 'f':
	case 'F':
		glRotatef(3.0, 1.0, 0.0, 0.0); /* pitch forward */
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		glRotatef(-3.0, 1.0, 0.0, 0.0); /* pitch back */
                glutPostRedisplay();
		break;
	case 'l':
	case 'L':
		glRotatef(3.0, 0.0, 0.0, 1.0); /* pitch back */
                glutPostRedisplay();
		break;

	case 'r':
	case 'R':
		glRotatef(-3.0, 0.0, 0.0, 1.0); /* pitch back */
                glutPostRedisplay();
		break;	
        default:
               break;
	}
}
