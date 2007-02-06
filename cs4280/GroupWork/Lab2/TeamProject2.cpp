#include <windows.h>
#include<gl/glut.h>
#include "canvas.h"

char TITLE[]            = "Team Project 2";
char *WINDOW_TITLE      = TITLE;
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int WINDOW_WIDTH  = 10;
const int WINDOW_HEIGHT = 10;
const float LEFT        = 3.0;
const float RIGHT       = 7.0;
const float BOTTOM      = 3.0;
const float TOP         = 6.0;

Canvas canvas1 = Canvas(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);

Point2 CohenSutherlandClip(Point2 p1, Point2 p2)
{
	unsigned char code = 0;
	if(p1.getX()<LEFT)   code |= 8;
	if(p1.getY()>TOP)    code |= 4;
	if(p1.getX()>RIGHT)  code |= 2;
	if(p1.getY()<BOTTOM) code |= 1;

	Point2 p(p1.getX(), p1.getY());
	float tempX, tempY;
	float dely = p2.getY() - p1.getY();
	float delx = p2.getX() - p1.getX();
	if(code & 8) {
		tempY = p.getY() + ((LEFT - p.getX()) * dely / delx);
		tempX = LEFT;
		p.set(tempX, tempY);
	}
	if(code & 2) {
		tempY = p.getY() + ((RIGHT - p.getX()) * dely / delx);
		tempX = RIGHT;
		p.set(tempX, tempY);
	}
	if(code & 1) {
		if(p.getY()<BOTTOM)
		{
			tempX = p.getX() + ((BOTTOM - p.getY()) * delx / dely);
			tempY = BOTTOM;
			p.set(tempX, tempY);
		}
	}
	if(code & 4) {
		if(p.getY()>TOP)
		{
			tempX = p.getX() + ((TOP - p.getY()) * delx / dely);
			tempY = TOP;
			p.set(tempX, tempY);
		}
	}
	return p;
}

bool equals(Point2 p1, Point2 p2)
{
	if((p1.getX()==p2.getX()) && (p1.getY()==p2.getY()))
		return  true;
	return false;
}
		
void display(void)
{
	canvas1.setWindow(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	canvas1.setViewport (0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);
	canvas1.clearScreen();
	//
	Color red(1.0, 0.0, 0.0);
	Color green(0.0, 1.0, 0.0);
	Color blue(0.0, 0.0, 1.0);
	canvas1.drawRect(LEFT, BOTTOM, RIGHT-LEFT, TOP-BOTTOM); //draw "clipping" rectangle
	//
	Point2 p1Ary[20];
	Point2 p2Ary[20];
	Line finalLineAry[60]; //there is a possibility of having 3 line segments per original line
	int numFinalLines = 0;
	//
	p1Ary[0].set(1.0, 8.0);
	p2Ary[0].set(8.0, 8.0);
	p1Ary[1].set(1.0, 2.0);
	p2Ary[1].set(9.0, 9.0);
	p1Ary[2].set(1.0, 7.5);
	p2Ary[2].set(1.0, 1.0);
	p1Ary[3].set(1.0, 8.0);
	p2Ary[3].set(8.0, 1.0);
	p1Ary[4].set(1.0, 6.0);
	p2Ary[4].set(7.0, 2.0);
	p1Ary[5].set(8.0, 6.0);
	p2Ary[5].set(2.0, 4.0);
	p1Ary[6].set(2.0, 4.0);
	p2Ary[6].set(8.0, 4.0);
	p1Ary[7].set(4.0, 4.5);
	p2Ary[7].set(6.0, 4.5);
	p1Ary[8].set(4.0, 5.0);
	p2Ary[8].set(4.0, 4.0);
	p1Ary[9].set(4.0, 4.0);
	p2Ary[9].set(8.0, 8.0);
	p1Ary[10].set(4.0, 8.0);
	p2Ary[10].set(4.0, 2.0);
	p1Ary[11].set(2.0, 1.0);
	p2Ary[11].set(8.0, 9.0);
    //
	for(int x=0; x<12; x++)
	{
		if((p1Ary[x].getX() < LEFT && p2Ary[x].getX() < LEFT) || (p1Ary[x].getX() > RIGHT && p2Ary[x].getX() > RIGHT) ||
			(p1Ary[x].getY() < BOTTOM && p2Ary[x].getY() < BOTTOM) || (p1Ary[x].getY() > TOP && p2Ary[x].getY() > TOP))
		{
			finalLineAry[numFinalLines].setPoint1(p1Ary[x]);
			finalLineAry[numFinalLines].setPoint2(p2Ary[x]);
			finalLineAry[numFinalLines].setColor(blue);
			numFinalLines++;
		}
		else 
		{
			Point2 tmpPnt1, tmpPnt2;
            tmpPnt1 = CohenSutherlandClip(p1Ary[x], p2Ary[x]);
			tmpPnt2 = CohenSutherlandClip(p2Ary[x], p1Ary[x]);
			//
			if(!(equals(p1Ary[x], tmpPnt1)))
			{
				finalLineAry[numFinalLines].setPoint1(p1Ary[x]);
				finalLineAry[numFinalLines].setPoint2(tmpPnt1);
				finalLineAry[numFinalLines].setColor(blue);
				numFinalLines++;
			}
			//
			if(!(equals(p2Ary[x], tmpPnt2)))
			{
				finalLineAry[numFinalLines].setPoint1(p2Ary[x]);
				finalLineAry[numFinalLines].setPoint2(tmpPnt2);
				finalLineAry[numFinalLines].setColor(blue);
				numFinalLines++;
			}
			//
			finalLineAry[numFinalLines].setPoint1(tmpPnt1);
			finalLineAry[numFinalLines].setPoint2(tmpPnt2);
			finalLineAry[numFinalLines].setColor(green);
			numFinalLines++;
		}

		for(int x=0; x<numFinalLines; x++)
		{
			canvas1.drawLine(finalLineAry[x]);
		}
	}
}	

int main(void)
{
	canvas1.setBackgroundColor(1.0,1.0,1.0);
	canvas1.setColor(1.0,0.0,0.0);
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}