#include <windows.h>
#include <stdio.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <gl/glut.h>

void init(void);
void display(void);

const int WINDOW_WIDTH = 600;
const int WINDOW_HEIGHT = 600;

bool initializeComplete = false;
bool drawLines = false;
bool movePoints = false;
bool moveLine = false;
bool movePoint1 = false;
bool movePoint2 = false;

class Point2
{
public:
	Point2() {x = y = 0.0f;} //constructor 1
	Point2(float xx, float yy) {x=xx; y=yy;} //constructor 2
	void set(float xx, float yy) {x=xx; y=yy;}
	float getX() {return x;}
	float getY() {return y;}
	void draw(void)
	{
		glBegin(GL_POINTS); //draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();
		glFlush();
	}
private:
	float x, y;
};

Point2 linePoint[2];
Point2 polyPoint[100];
int polyIndex = 0;
int numPoints = 0;
int pointIndex = 0;
bool moveEnabled = false;
bool enablePointDrag = false;

void myKeyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
		case 'c':
		case 'C':
			initializeComplete = true;
			drawLines = false;
			movePoints = false;
			moveLine = false;
			break;
		default:
			break;
		case 'd':
		case 'D':
			if (initializeComplete == true)
				drawLines = true;
			break;
		case 'p':
		case 'P':
			if (initializeComplete == true)
				movePoints = true;
			break;
		case 'm':
		case 'M':
			if (initializeComplete == true)
				moveLine = true;
			break;
    }
}

void myMovedMouse(int x, int y)
{
	if (moveEnabled == true)
	{
		polyPoint[pointIndex].set((float) x, (float) (WINDOW_HEIGHT-y));
		glutPostRedisplay();
	}
	if (drawLines == true)
	{
		linePoint[1].set((float) x, (float) (WINDOW_HEIGHT-y));
		glutPostRedisplay();
	}
	if (moveLine == true)
	{
		if (movePoint1 == true)
		{
			linePoint[0].set((float) x, (float) (WINDOW_HEIGHT-y));
			glutPostRedisplay();
		}
		else if (movePoint2 == true)
		{
			linePoint[1].set((float) x, (float) (WINDOW_HEIGHT-y));
			glutPostRedisplay();
		}
	}
}


void myMouse(int button, int state, int x, int y)
{
	if (initializeComplete == false)
	{
		if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
		{
			polyPoint[numPoints].set((float) x, (float) (WINDOW_HEIGHT-y));
			++numPoints;
			glutPostRedisplay();
		}
	}
	else
	{
		if (movePoints == true)
		{
			if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
			{
				moveEnabled = false;
				for (int index=0; index<numPoints; index++)
				{
					if ((x < ((int)polyPoint[index].getX() + 20)) &&
						(x > ((int)polyPoint[index].getX() - 20)) &&
						(y < (WINDOW_HEIGHT - (int)polyPoint[index].getY() + 20)) &&
						(y > (WINDOW_HEIGHT - (int)polyPoint[index].getY() - 20)))
					{
						moveEnabled = true;
						pointIndex = index;
					}
				}
			}
			if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP))
				moveEnabled = false;
		}
		else if (drawLines == true)
		{
			if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
				linePoint[0].set((float) x, (float) (WINDOW_HEIGHT-y));
		}
		else if (moveLine == true)
		{
			movePoint1 = false;
			movePoint2 = false;
			if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN))
			{
				if ((x < ((int)linePoint[0].getX() + 20)) &&
					(x > ((int)linePoint[0].getX() - 20)) &&
					(y < (WINDOW_HEIGHT - (int)linePoint[0].getY() + 20)) &&
					(y > (WINDOW_HEIGHT - (int)linePoint[0].getY() - 20)))
					movePoint1 = true;
				else if ((x < ((int)linePoint[1].getX() + 20)) &&
						(x > ((int)linePoint[1].getX() - 20)) &&
						(y < (WINDOW_HEIGHT - (int)linePoint[1].getY() + 20)) &&
						(y > (WINDOW_HEIGHT - (int)linePoint[1].getY() - 20)))
						movePoint2 = true;
			}
		}
	}
}
 
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("A 3D Object");
    init();
    glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMovedMouse);
    glutMainLoop();
    return 0;
}
 
void init(void)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
 
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);    
	//printf("Trying to draw!\n");
	glBegin(GL_LINE_LOOP);
	for (int x=0; x<numPoints; x++)
	{
		glVertex2f(polyPoint[x].getX(), polyPoint[x].getY());
	}
	glEnd();
	glBegin(GL_LINES);
	for (int x=0; x<2; x++)
	{
		glVertex2f(linePoint[x].getX(), linePoint[x].getY());
	}
	glEnd();
	glutSwapBuffers();
}
