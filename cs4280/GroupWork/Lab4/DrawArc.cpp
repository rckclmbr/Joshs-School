#include<windows.h>
#include<gl/gl.h>
#include<gl/glu.h>
#include<gl/glut.h>

#include"canvas.h"

using namespace std;
void drawArc2(Point2 c, double R, double startAngle, double sweep);

Canvas cvs(600,600,"Draw Arc 2");

void myDisplay(void)
{
	cvs.clearScreen();
	Point2 center(0,0);
	cvs.setColor(1,0,1);
	glLineWidth(2);

//draw arc call
	drawArc2(center,25,80,145);

	glFlush();
}

//main function
void main()
{
	cvs.setBackgroundColor(1,1,1);
	cvs.setWindow(-100,100,-100,100);
	glutDisplayFunc(myDisplay);

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

