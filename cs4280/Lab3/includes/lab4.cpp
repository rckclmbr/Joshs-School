#include "includes/header.h"
#include "includes/canvas.h"
#include <iostream>
using namespace std;

void redraw(void);

Canvas cvs(600,600,"Rotations!"); //global canvas object
bool repost;

class Rectangle {
	private:
		float center;
		RealRect r;
	public:
		Rectangle() {
			cvs.moveTo(0,0);
			center = 0.0;
			r = RealRect();
			reposition();
		}

		void reposition() {
			r.set(center - 10.0, center + 10.0, center - 20.0, center + 20.0);
		}

		void draw() {
			r.draw();
		}
};
	
Rectangle temp = Rectangle();

void display(void)
{


	// Draw axis
	cvs.clearScreen();//clear screen
	cvs.setColor(1.0,0.0,0.0);
	cvs.moveTo(-100,0);
	cvs.lineTo(100,0);
	cvs.moveTo(0,-100);
	cvs.lineTo(0,100);

	glPushMatrix();
	if(repost) {
		glTranslatef(0.0,12.0,0.0);
	}
	temp.draw();
	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y) {
	repost = true;
	glutPostRedisplay();
}


int main(int argc, char* argv[])
{
	//the window is opened in the Canvas constructor 
	cvs.setBackgroundColor(1.0,1.0,1.0); //background is white
	cvs.setColor(0.0,0.0,0.0); //set drawing color

	cvs.setWindow(-100.0,100.0,-100.0,100.0);
	cvs.setViewport(0,600,0,600);

	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
