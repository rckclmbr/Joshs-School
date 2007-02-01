#include "header.h"

void init(void);
void checkerboard(int size);
void display(void);

int main (int argc, char **argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("A Checkerboard");
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
	glOrtho(0.0, 80.0, 0.0, 80.0, 0.0, 80.0);
}

void display(void) {

	glClear(GL_COLOR_BUFFER_BIT);
	checkerboard(10);
	glutSwapBuffers();
}

void checkerboard(int size)
{
	int i = 0, j = 0;


	for(i = 0; i < 8; i++) {
		for(j = 0; j < 8; j++) {

			if((i + j) % 2 == 0)
				glColor3f(1,1,1);
			else
				glColor3f(0,0,1);

			int x = i * size;
			int y = j * size;

			glBegin(GL_QUADS);
				glVertex3f(x, y, 0.0);
				glVertex3f(x + size, y, 0.0);
				glVertex3f(x + size, y + size, 0.0);
				glVertex3f(x, size + y, 0.0);
			glEnd();
		}
	}
}
