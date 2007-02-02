#include "includes/header.h"
#include "includes/canvas.h"

Canvas cvs(640,240,"A turtle!"); //global canvas object
 
void display(void)
{
    cvs.clearScreen();//clear screen
    cvs.setWindow(-50.0,20.0,0,35.0);
    cvs.setViewport(10,640,10,240);
    
	// Move for part 1
	cvs.moveTo(-49,2);
	cvs.turnTo(0);

	// Draw part 1
	for(int x = 20; x > 1; x -= 4) {
		for(int y = 0; y < 4; y++) {
			cvs.forward(x,1);
			cvs.turn(90);
		}
	}
	
	// Move for part 2
	cvs.moveTo(-25,2);
	cvs.turnTo(0);
	
	// Draw part 2
	for(int x = 20; x > 1; x --) {
		cvs.forward(x,1);
		cvs.turn(90);
	}

	// Move for part 3
	cvs.moveTo(0,2);
	cvs.turnTo(0);

	// Draw part 3 WITHOUT lifting the pen
	cvs.forward(20,1);
	cvs.turn(120);
	cvs.forward(20,1);
	cvs.turn(120);
	cvs.forward(10,1);
	cvs.turn(120);
	cvs.forward(10,1);
	cvs.turn(-120);
	cvs.forward(10,1);
	cvs.turn(-120);
	cvs.forward(10,1);
	cvs.turn(120);
	cvs.forward(10,1);
}


int main(int argc, char* argv[])
{
    //the window is opened in the Canvas constructor 
    cvs.setBackgroundColor(1.0,1.0,1.0); //background is white
    cvs.setColor(0.0,0.0,0.0); //set drawing color
    glutDisplayFunc(display);
    glutMainLoop();
    
    return 0;
}

