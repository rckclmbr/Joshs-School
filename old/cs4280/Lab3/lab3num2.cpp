#include "includes/header.h"
#include "includes/canvas.h"

void drawStars(int number, int radius, int distance, int rotAngle);
void ngon(Point2* pt, int n, float cx, float cy, float radius, int rotAngle, int isStar);

Canvas cvs(640,640,"Stars!"); //global canvas object
const float PI = 3.14159265;
	
void display(void)
{
	cvs.clearScreen();//clear screen
	cvs.setWindow(-50.0,50.0,-50.0,50.0);
	cvs.setViewport(10,640,10,640);
   
	cvs.moveTo(0,0);
   	drawStars(1,10,35,18);
   	drawStars(10,2,15,0);
   	drawStars(10,5,25,18);

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

void drawStars(int number, int radius, int distance, int rotAngle) {

	Point2 circle[number];
	ngon(circle,number,0,0,distance, rotAngle, 0);
	
	// Draw all the stars in the loop
	int POINTS = 5;
	for(int j = 0; j < number; j++) {
		// Draw an individual star	
		Point2 pt[POINTS];
		ngon(pt, POINTS, circle[j].getX(), circle[j].getY(), radius, 18, 1);
		cvs.moveTo(pt[0]);
		for(int i = 0; i < POINTS; i++) {
			cvs.lineTo(pt[i + 1]);
		}
	}

}



// This does WAY too much, but will suffice for the assignment
void ngon(Point2* pt, int n, float cx, float cy, float radius, int rotAngle, int isStar)
{

	if(n < 3) return;
		
	double angle = rotAngle * PI / 180; // Initial angle
	double angleInc = 2 * PI / n;		// Angle increment
	
	
	for(int k = 0; k < n + 1; k++) {
		float x = radius * cos(angle) + cx;
		float y = radius * sin(angle) + cy;
		
		pt[k].set(x, y);
		
		if(isStar == 0)
			angle += angleInc;
		else
			angle += 2 * angleInc; // So it will draw the star appropriatly
	}
}
