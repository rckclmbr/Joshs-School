#include "header.h"

class GLintPoint{
public: 
		GLint x, y;
};


void init(void);
void drawDiamond(GLintPoint center, int d);
void display(void);
GLintPoint getRandomPoint(int offset);

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
	glOrtho(0.0, 100.0, 0.0, 100.0, 0.0, 100.0);
}

void display(void) {
	int diameter;		// Diameter of the diamond
	GLintPoint vertex;	// Vertex of the diamond

	glClear(GL_COLOR_BUFFER_BIT);
	
	for(int i = 0; i < 20; i++) {
	
		glColor3f(rand() % 100 / 100.0,
					rand() % 100 / 100.0,
					rand() % 100 / 100.0);
		
		diameter = rand() % 20;
		vertex = getRandomPoint(diameter);
								
		drawDiamond(vertex, diameter);
	}
	
	glutSwapBuffers();
}

void drawDiamond(GLintPoint center, int d)
{
		float rad = d / 2;
		
		glBegin(GL_QUADS);
			glVertex3f(center.x + rad, center.y, 0.0);
			glVertex3f(center.x, center.y + rad, 0.0);
			glVertex3f(center.x - rad, center.y, 0.0);
			glVertex3f(center.x,  center.y - rad, 0.0);
		glEnd();
		
}

GLintPoint getRandomPoint(int offset) {
	offset = offset / 2;
	int x = rand() % (100 - offset * 2) + offset;
	int y = rand() % (100 - offset * 2) + offset;
	return (GLintPoint) {x: x, y: y};
}

