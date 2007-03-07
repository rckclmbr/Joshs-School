//						Learning Team C
//						Members:
//							Lorin Kartchner
//							Todd William Brown
//							Royce Judd
//							Josh Braegger
//							Jeremiah Stephenson
//                      CS 4280 – 7:30 pm
//                      Section 4 Learning Team Assignment
//                      Mr. Rague
//                      Due: 03/7/07
//                      Version: 1.0
// -----------------------------------------------------------------
//  This program uses the drawArc2 routine as illustrated in the text on page 280, figure 6.68 to 
//  to draw arcs.
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0
//		Date: Wrote the documentation for the project
//
//
//		Team Member: Todd William Brown
//		Version 1.0
//		Date: Completed task number three for the project
//		
//
//		Team Member: Royce Judd
//		Version 1.0
//		Date: Wrote this program to satisfy portion five of the project, DrawArc
//		
//
//		Team Member: Josh Braegger
//		Version 1.0
//		Date: Completed task number one and two of the project
//		
//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
//		Date: 3/3/2007
//		Wrote the program for the fourth portion of the group assignment, npoints



#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>

#include"canvas.h"

using namespace std;
void drawArc2(Point2 c, double R, double startAngle, double sweep);

Canvas cvs(600,600,"Draw Arc 2");
double radius = 10;
double sAngle = 0;
double swAngle = 90;
bool startORsweep = true;

//arrow keyboard display
void myKeyboard(int key, int x,int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			{
				radius++;
				break;
			}
		case GLUT_KEY_DOWN:
			{
				radius--;
				break;
			}
		case GLUT_KEY_RIGHT:
			{
				if(startORsweep == true)
					sAngle++;
				else
					swAngle++;
				break;
			}
		case GLUT_KEY_LEFT:
			{
				if(startORsweep == true)
					sAngle--;
				else
					swAngle--;
				break;
			}
		default:
			{}
	}
	glutPostRedisplay();
}
//normal keyboard function
void myKeys(unsigned char key, int x, int y)
{
	switch(key)
	{
	case 's':
		{
			if(startORsweep == true)
				startORsweep = false;
			else
				startORsweep = true;
		}
	default:
		{}
	}
}
//display function
void myDisplay(void)
{
	cvs.clearScreen();
	Point2 center(0,0);
	cvs.setColor(1,0,1);
	glLineWidth(2);

//draw arc call
	drawArc2(center,radius,sAngle,swAngle);

	glFlush();
}

//main function
void main()
{
	cvs.setBackgroundColor(1,1,1);
	cvs.setWindow(-100,100,-100,100);
	glutDisplayFunc(myDisplay);
	glutSpecialFunc(myKeyboard);
	glutKeyboardFunc(myKeys);
	glutMainLoop();
}

//draw arc2 function
void drawArc2(Point2 c, double R, double startAngle, double sweep)
{
	const int n=30;
	const double RadPerDeg = .01745329;
	double delang = RadPerDeg * sweep/n;
	double T = tan(delang/2);
	double S = 2*T/(1+T*T);
	double snR = R*sin(RadPerDeg*startAngle);
	double csR = R*cos(RadPerDeg*startAngle);
	cvs.moveTo(c.getX(),c.getY());
	cvs.lineTo(c.getX()+csR,c.getY()+snR);
	
	for(int i=1;i<n;i++)
	{
		snR += T * csR;
		csR -= S * snR;
		snR += T * csR;
		cvs.lineTo(c.getX()+csR,c.getY()+snR);
	}
	cvs.lineTo(c.getX(),c.getY());
}

