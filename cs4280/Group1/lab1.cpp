#include "header.h"

static int WIDTH = 600;
static int HEIGHT = 400;
static float GOLDEN_RATIO = .618033;
typedef enum direction {UP, DOWN, LEFT, RIGHT};

class GLfloatPoint { public: float x,y; };	// A point on the graph

class GLRectangle {
	public: 
		GLfloat width, height;
		GLfloatPoint bottomLeft;
		direction pos;					// This is the location the square 
										// is going to be in the rectangle

		GLRectangle() { };
		GLRectangle(GLfloat, GLfloat);
		void drawRectangle();
		void getNewRectangleCoords();

	private:
		void moveLocation();
};

// 2-argument constructor
GLRectangle::GLRectangle(GLfloat w, GLfloat h) { 
	pos = LEFT; 

	// Get whether to clip the rectangle by width or height
	if(w / h > GOLDEN_RATIO) {
		width = w;
		height = w * GOLDEN_RATIO;
	} else {
		width = h * GOLDEN_RATIO;
		height = h;
	}

	bottomLeft.x = 0;
	bottomLeft.y = 0;
	
	// Now center it in the window
	if(w > width)
		bottomLeft.x = (w - width) / 2;
	if(h > height)
		bottomLeft.y = (h - height) / 2;

}

// Moves the rectangle for the next position (so it goes in a circle)
void GLRectangle::moveLocation() {
	if(pos == UP) pos = RIGHT;
	else if(pos == RIGHT) pos = DOWN;
	else if(pos == DOWN) pos = LEFT;
	else if(pos == LEFT) pos = UP;
}

void GLRectangle::getNewRectangleCoords() {
	// x will be the length of the short side
	float x = width - height;
	if(x < 0) x *= -1;
	// y will be the length of the long side
	float y = (width < height) ? width : height;

	// If the position of the box is at the top, then
	// we want the long side to be the width
	if(pos == UP || pos == DOWN) {
		width = y;
		height = x;
	// Otherwise we want the long side to be the height
	} else {
		width = x;
		height = y;
	}

	// Now we get the new position of the bottom-left coordinate
	switch(pos) {
		case DOWN:
			bottomLeft.y = bottomLeft.y + y;
			break;
		case LEFT:
			bottomLeft.x = bottomLeft.x + y;
			break;
	}
	moveLocation(); // Move square location for next iteration
}

// This draws the rectangle
void GLRectangle::drawRectangle() {
	// Different colors, so we can distinguish where one begins
	// and one ends
	if(pos == UP)
		glColor3f(0,0,1);
	else if(pos == RIGHT)
		glColor3f(1,0,1);
	else if(pos == DOWN)
		glColor3f(1,1,1);
	else if(pos == LEFT)
		glColor3f(0,1,1);

	glBegin(GL_QUADS);
		glVertex3f(bottomLeft.x, bottomLeft.y, 0.0);
		glVertex3f(bottomLeft.x, bottomLeft.y + height, 0.0);
		glVertex3f(bottomLeft.x + width, bottomLeft.y + height, 0.0);
		glVertex3f(bottomLeft.x + width, bottomLeft.y, 0.0);
	glEnd();
}

void init(void);
void display(void);

int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("A Golden Rectangle");
	init();
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 100.0);
}

void display(void) {
	int diameter;		// Diameter of the diamond
	GLRectangle* rect = new GLRectangle(WIDTH, HEIGHT);

	glClear(GL_COLOR_BUFFER_BIT);

	while(rect->width > 1) {
		rect->drawRectangle();
		rect->getNewRectangleCoords();
	}
	
	glutSwapBuffers();
}
