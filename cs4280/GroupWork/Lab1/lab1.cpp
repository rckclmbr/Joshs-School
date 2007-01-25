// -----------------------------------------------------------------
//                      Learning Team c
//                      Members:
//                      Lorin Kartchner
//						Todd Brown
//						Royce Judd
//						Josh Braegger
//                      CS 4280 – 7:30 pm
//                      Section 1 Learning Team Assignment
//                      Mr. Rague
//                      Due: 01/24/07
//                      Version: 1.2
// -----------------------------------------------------------------
//  This program finds the size of the biggest golden rectangle that
//  will fit on the viewing window. It then continualy takes sqaures
//  out forming smaller golden rectangles. It stops when the golden 
//  rectangle has a width of 1
// -----------------------------------------------------------------
#include "header.h"

static int WIDTH = 600;  //width of window
static int HEIGHT = 400;  //height of window
static float GOLDEN_RATIO = .618033;  //golden ratio
typedef enum direction {UP, DOWN, LEFT, RIGHT};

class GLfloatPoint { public: float x,y; };	// A point on the graph

//class to define a rectangle
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

	// Get whether to clip the rectangle by width or h
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
	//if(pos == UP)
	//	glColor3f(0,0,1);
	//else if(pos == RIGHT)
	//	glColor3f(1,0,1);
	//else if(pos == DOWN)
	//	glColor3f(1,1,1);
	//else if(pos == LEFT)
	//	glColor3f(0,1,1);

	glBegin(GL_LINE_LOOP);
		glVertex3f(bottomLeft.x, bottomLeft.y, 0.0);
		glVertex3f(bottomLeft.x, bottomLeft.y + height, 0.0);
		glVertex3f(bottomLeft.x + width, bottomLeft.y + height, 0.0);
		glVertex3f(bottomLeft.x + width, bottomLeft.y, 0.0);
	glEnd();
}

void init(void);
void display(void);

//main GL function
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

//GL initalize function
void init(void) {
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, WIDTH, 0.0, HEIGHT, 0.0, 100.0);
}

//GL display function
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

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//       Team Member:  Josh Braegger
//       Version: 1.0
//       Date:  01/22/07
//       Wrote the functionality of the code
//		 Version: 1.0

//       Team Member:  Royce Judd
//       Version: 1.1
//       Date:  01/22/07
//       Added header and comments in the code
//		 Version: 1.2

