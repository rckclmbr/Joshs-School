//						Learning Team C
//						Members:
//							Lorin Kartchner
//							Todd William Brown
//							Royce Judd
//							Josh Braegger
//							Jeremiah Stephenson
//                      CS 4280 – 7:30 pm
//                      Section 2 Learning Team Assignment
//                      Mr. Rague
//                      Due: 02/07/06
//                      Version: 1.0
// -----------------------------------------------------------------
// This is the header file for the TeamProject2 assignment.  This 
// file contains the class declarations as well as some definitions
// of methods contained in the classes.  The classes Point2, IntRect,
// RealRect, and Canvas were developed using code samples from the 
// text book between pages 101 and 105.  There are additional
// classes contained here that were written for this assignement such
// as Color and Line.  The methods that are not defined in this file
// are defined in Canvas.cpp
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0
//		Date: 02/07/2007
//		Conducting the peer review. 
//
//		Team Member: Todd William Brown
//		Version 1.0
//		Date: 02/06/2007
//		Developed the algorithm, and implemented the code.
//
//		Team Member: Royce Judd
//		Version 1.0
//		Date 02/07/2007
//		Presenting the code in class.
//
//		Team Member: Josh Braegger
//		Version 1.0
//		Date 02/06/2007
//		Wrote the documentation to go with the code.
//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
//		Date 02/06/2007
//		Wrote the comments throughout the source code including the headers


#include <windows.h>			//compiler directives
#include<gl/glut.h>
#include "canvas.h"

char TITLE[]            = "Team Project 2";			//title that appears in the window
char *WINDOW_TITLE      = TITLE;
const int SCREEN_WIDTH  = 640;						//value that is to be used for the screen width
const int SCREEN_HEIGHT = 480;						//value that is to be used for the screen height
const int WINDOW_WIDTH  = 10;						//value that is to be used to set the width of the world window
const int WINDOW_HEIGHT = 10;						//value that is to be used to set the height of the world window
const float LEFT        = 3.0;
const float RIGHT       = 7.0;						//these are the values for the rectangle to be drawn
const float BOTTOM      = 3.0;
const float TOP         = 6.0;

Canvas canvas1 = Canvas(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);		//global canvas object

unsigned char getCode(Point2 p)				//This function returns a bitwise OR value
{
	unsigned char code = 0;
	if(p.getX()<LEFT)   code |= 8;			//if on the left, then TFFF or 1000
	if(p.getY()>TOP)    code |= 4;			//if on the top, then FTFF or 0100
	if(p.getX()>RIGHT)  code |= 2;			//if on the right, then FFTF or 0010
	if(p.getY()<BOTTOM) code |= 1;			//if on the bottom, then FFFT or 0001
	return code;							
}

Point2 CohenSutherlandClip(Point2 p1, Point2 p2)	//function to tell us if the line intersects with the rectangle	
{													//returns a set of points if such intersection occurs
	unsigned char code = getCode(p1);			//takes the first point to test the location
	Point2 p(p1.getX(), p1.getY());				//takes the first point and places it into a local variable
	float tempX, tempY;							
	float dely = p2.getY() - p1.getY();			//these values help determine the slope of the line
	float delx = p2.getX() - p1.getX();
	if(code & 8) {								//to the left
		tempY = p.getY() + ((LEFT - p.getX()) * dely / delx);		//obtains the y value where the line crosses
		tempX = LEFT;												//obtains the x value where the line crosses
		p.set(tempX, tempY);									//places these values into p
	}
	if(code & 2) {								//to the right
		tempY = p.getY() + ((RIGHT - p.getX()) * dely / delx);		//obtains the y value where the line crosses
		tempX = RIGHT;												//obtains the x value where the line crosses
		p.set(tempX, tempY);									//places these value into p
	}
	if(code & 1) {								//to the bottom
		if(p.getY()<BOTTOM)										
		{
			tempX = p.getX() + ((BOTTOM - p.getY()) * delx / dely);		//obtains the x value where line crosses
			tempY = BOTTOM;												//obtains the y value where line crosses
			p.set(tempX, tempY);
		}
	}
	if(code & 4) {
		if(p.getY()>TOP)						//to the top
		{
			tempX = p.getX() + ((TOP - p.getY()) * delx / dely);		//obtains the x value where line crosses
			tempY = TOP;												//obtains the y value where line crosses
			p.set(tempX, tempY);
		}
	}
	return p;					//returns the point where the line intersects with the rectangle
}

bool equals(Point2 p1, Point2 p2)		//this tests to see if two sets of points are the same
{
	if((p1.getX()==p2.getX()) && (p1.getY()==p2.getY()))
		return  true;
	return false;
}

void display(void)
{
	canvas1.setWindow(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);			//sets the orthagonical view
	canvas1.setViewport (0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);		//sets the viewport
	canvas1.clearScreen();											//clears the screen
	//
	Color red(1.0, 0.0, 0.0);							
	Color black(0.0, 0.0, 0.0);
	canvas1.drawRect(LEFT, BOTTOM, RIGHT-LEFT, TOP-BOTTOM); //draw "clipping" rectangle
	//
	Point2 p1Ary[11];
	Point2 p2Ary[11];
	Line finalLineAry[30]; //there is a possibility of having 3 line segments per original line
	int numFinalLines = 0;
	//
	p1Ary[0].set(2.0, 7.0);			//these are the point values in the array
	p2Ary[0].set(8.0, 7.0);			//An array is being used so that there is control
	p1Ary[1].set(1.0, 2.0);			//over instances of certain cases.  An example
	p2Ary[1].set(1.0, 7.0);			//is so that it could test vertical and horizontal
	p1Ary[2].set(5.0, 2.5);			//lines.
	p2Ary[2].set(5.0, 6.5);
	p1Ary[3].set(2.0, 4.5);
	p2Ary[3].set(8.0, 4.5);
	p1Ary[4].set(3.2, 2.4);
	p2Ary[4].set(6.8, 6.6);
	p1Ary[5].set(2.4, 3.2);
	p2Ary[5].set(7.6, 5.8);
	p1Ary[6].set(2.4, 5.8);
	p2Ary[6].set(7.6, 3.2);
	p1Ary[7].set(3.2, 6.6);
	p2Ary[7].set(6.8, 2.4);
	p1Ary[8].set(3.4, 5.6);
	p2Ary[8].set(6.6, 5.6);
	p1Ary[9].set(9.0, 8.0);
	p2Ary[9].set(1.0, 1.0);
	p1Ary[10].set(3.4,5.4);
	p2Ary[10].set(3.4,3.6);
	//
	for(int x=0; x<10; x++)
	{														//this uses an AND operator between two points
		if((getCode(p1Ary[x]) & getCode(p2Ary[x]))!= 0)		//if the result is not zero, then they are in the same region
		{													
			finalLineAry[x].setLine(p1Ary[x], p2Ary[x], black);		//stores a black line in the final line array
			numFinalLines++;				//keeps track of how many lines are in the array
		}
		else			//if the AND operator returns zero then the two values were different
		{
			Point2 tmpPnt1, tmpPnt2;							
            tmpPnt1 = CohenSutherlandClip(p1Ary[x], p2Ary[x]);	//returns the point, if any, where the line crosses the rectangle from one side
			tmpPnt2 = CohenSutherlandClip(p2Ary[x], p1Ary[x]); //returns the point, if any, where the line crosses the rectangle from the other side
			//
			if(!(equals(p1Ary[x], tmpPnt1)))		//if the two points do not equal								
			{
				finalLineAry[numFinalLines].setLine(p1Ary[x], tmpPnt1, black);		//this will draw the part that it outside of the rectangle
				numFinalLines++;
			}
			if(!(equals(p2Ary[x], tmpPnt2)))		//if the two points do not equal
			{
				finalLineAry[numFinalLines].setLine(p2Ary[x], tmpPnt2, black);		//this will draw the part that it outside of the rectangle
				numFinalLines++;
			}
			finalLineAry[numFinalLines].setLine(tmpPnt1, tmpPnt2, red);		//this will draw the part of the line that is inside the rectangle
			numFinalLines++;
		}

		for(int x=0; x<numFinalLines; x++)		//this loops through the final line array and
		{										//draws the lines
			canvas1.drawLine(finalLineAry[x]);
		}
	}
}	

int main(void)
{
	canvas1.setBackgroundColor(1.0,1.0,1.0);		//sets background color to white
	canvas1.setColor(0.0,0.0,1.0);				//sets the canvas color blue
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}