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
//                      Due: 03/28/06
//                      Version: 1.0
// -----------------------------------------------------------------
// Creates a scene and allows for a camera to move through it.
// A grid can be turned on and off to help notice movement
// -----------------------------------------------------------------

// -----------------------------------------------------------------
//   Change Control Section
// -----------------------------------------------------------------
//		Team Member: Lorin Kartchner
//		Version 1.0

//
//		Team Member: Todd William Brown
//		Version 1.0

//
//		Team Member: Royce Judd
//		Version 1.0

//
//		Team Member: Josh Braegger
//		Version 1.0

//
//		Team Member: Jeremiah Stephenson
//		Version 1.0
/////////////////////////////////////////////////////////////////////////////
#include "Camera.h"

// Controls the ratio, just to make things faster if we want
const float RAT = 2.0;

// Variable declarations
Camera cam; // global camera object
bool toggle = true;
float nVal = 7;
bool fly = false;

bool foward=false;
bool back=false;
bool left1 =false;
bool right1 = false;
bool up = false;
bool down = false;
bool rollleft = false;
bool rollright = false;

// Function declarations
void snowman(void);
void ramp(void);
void rings(void);
void cones(void);
void steps(void);

typedef struct materialStruct{
	GLfloat ambient[4];
	GLfloat diffuse[4];
	GLfloat specular[4];
	GLfloat shininess;
} materialStruct;

//different materials
materialStruct brassMaterials = {
	{0.33,0.22,.03,1.0},
	{.78,.57,.11,1.0},
	{.99,.91,.81,1.0},
	27.8
};
materialStruct redPlastic = {
	{0.3,0,0,1},
	{0.6,0,0,1},
	{.8,.6,.6,1},
	60
};
materialStruct whiteShiney = {
	{1,0,1,1},
	{1,0,1,1},
	{1,1,1,1},
	50
};

materialStruct crazyShiney = {
	{0.6,0,.3,1},
	{.2,0,1.6,1},
	{1.6,1,.25,1},
	100
};

void materials(materialStruct *materials)
{
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,materials ->ambient);
	glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,materials->diffuse);
	glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,materials->specular);
	glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,materials->shininess);
}


//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y)
{
  switch(key)
  {	
	// controls for camera
	case 'F':    cam.slide(0,0,-0.2);break; // slide camera forward
	case 'F'-64: cam.slide(0,0,0.2); break; //slide camera back	
	case 'U':    cam.slide(0,-0.2,0);break; // slide camera upward
	case 'U'-64: cam.slide(0,0.2,0); break; //slide camera downward	
	case 'L':    cam.slide(0.2,0,0);break; // slide camera left
	case 'L'-64: cam.slide(-0.2,0,0); break; //slide camera right	
	case 'T':    cam.roll(-1.);break; // roll camera CW
	case 'T'-64: cam.roll(1.); break; //roll camera CCW	
	case 'P':    cam.pitch(1.);break; // pitch camera up
	case 'P'-64: cam.pitch(-1.); break; //pitch camera down	
	case 'Y':    cam.yaw(-1.);break; // yaw camera right
	case 'Y'-64: cam.yaw(1.);break; // yaw camera right
	case 'V':    cam.vAngle( 1.);break; // increase Viewangle 
	case 'V'-64: cam.vAngle(-1.);break; // decrease Viewangle 
	case 'A':    cam.aRatio( .1);break; // increase Aspect Ratio 
	case 'A'-64: cam.aRatio(-.1);break; // decrease Aspect Ratio 
	case 'G':    toggle = !toggle;break; //toggles grid lines on and off
	case 'R':    cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);	cam.set(0, 2, 7, 0, 0, 0, 0, 1, 0); fly = false; break;//resets potision
	case 'M':    fly = !fly;break; //To fly the camera--MUST BE DONE AT THE BEGINGING BEFORE MANUAL MOVEMENT OR AFTER RESET
	//controls for continuous motion camera
	case 'w':	up = !up;				down = false;	break;
	case 's':	down = !down;			up = false;		break;
	case 'a':	rollleft = !rollleft;	rollright = false; break;
	case 'd':	rollright = !rollright;	rollleft = false;break;
  }
	glutPostRedisplay(); // draw it again
}
//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_UP:		foward	= !foward;	back = false; break;
		case GLUT_KEY_DOWN:		back	= !back;	foward = false; break;
		case GLUT_KEY_LEFT:		left1	= !left1;   right1 = false; break;
		case GLUT_KEY_RIGHT:	right1	= !right1;	left1 = false;
	}
	glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
//make things solid instead of crazy
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
//create light source and position
	GLfloat light_pos1[] = {5.0,5.0,5.0,0.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);

//draw different physical objects
	snowman();
	ramp();
	rings();
	cones();
	steps();

	cam.drawGridLines(toggle);

	glutSwapBuffers(); // display the screen just made
}

void Idle(void)
{
	Sleep(25);
	if (fly == true)
	{
		cam.yaw(1.);
		nVal += .02;
		cam.slide(-(sin(3.14159265/180 * nVal)),0.0,.02);
		
	}
	else
		nVal = 7.;
	//allows for continous motion in the idle state
	if(foward)	cam.slide(0,0,-0.1 * RAT);
	if(back)	cam.slide(0,0,.1 * RAT);
	if(left1)	cam.yaw(-.5 * RAT);
	if(right1)	cam.yaw(.5 * RAT);
	if(up)		cam.pitch(-.5 * RAT);
	if(down)	cam.pitch(.5 * RAT);
	if(rollleft)cam.roll(.5 * RAT);
	if(rollright)cam.roll(-.5 * RAT);
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffering
	glutInitWindowSize(640,480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("fly a camera around a scene");
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(Idle);
	glClearColor(1.0f,1.0f,1.0f,0.0f);  // background is white 
    glViewport(0, 0, 640, 480);
	cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);
	cam.set(0, 1, 15, 0, 0, 0, 0, 1, 0); // make the initial camera
	glutMainLoop();
}

void snowman(void)
{
	glPushMatrix();
		materials(&redPlastic);
		glTranslatef(-10,1,10);
		glutSolidSphere(1,100,100);
		glTranslatef(0,1.3,0);
		glutSolidSphere(.6,100,100);
		glTranslatef(0,0.75,0);
		glutSolidSphere(0.4,100,100);
	glPopMatrix();
}

void ramp(void)
{
	glPushMatrix();
		materials(&brassMaterials);
		glTranslatef(0,2,-5);
		glRotatef(30,1,0,0);
		glScaled(2, 0.3, 10);
		glutSolidCube(1.0);
	glPopMatrix();

}

void rings(void)
{
	glPushMatrix();
		materials(&redPlastic);
		glTranslatef(0, 5, -6);
		glutSolidTorus(2,4.8,100,100);
	glPopMatrix();

	glPushMatrix();
		materials(&whiteShiney);
		glTranslatef(0,6.3,-15);
		glutSolidTorus(0.1, 2.2,100,100);
		glTranslatef(0,-.5,-10);
		glutSolidTorus(0.1, 1.5, 100, 100);
	glPopMatrix();
}

void cones(void)
{
	glPushMatrix();
		materials(&redPlastic);
		glTranslatef(-10, 0, -6);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,6,100,100);
	glPopMatrix();

	glPushMatrix();
		materials(&redPlastic);
		glTranslatef(-20, 0, 9);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,6,100,100);
	glPopMatrix();

	glPushMatrix();
		materials(&crazyShiney);
		glTranslatef(10, 0, -15);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,6,100,100);
	glPopMatrix();

	glPushMatrix();
		materials(&redPlastic);
		glTranslatef(15, 0, -10);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,6,100,100);
	glPopMatrix();

	glPushMatrix();
		materials(&brassMaterials);
		glTranslatef(-5, 0, 16);
		glRotatef(-90,1,0,0);
		glutSolidCone(2,6,100,100);
	glPopMatrix();

}

void steps(void)
{
	
	glPushMatrix();
		materials(&crazyShiney);
		glTranslatef(15, 1, 0);
		glScalef(5,0.3,5);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(.5, 2, 0);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(.5, 2, 0);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(.5, 2, 0);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(.5, 2, 0);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(0, -2, -.5);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(0, -2, -.5);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(0, -2, -.5);
		glutSolidCube(1.0);
	
		materials(&crazyShiney);
		glTranslatef(0, -2, -.5);
		glutSolidCube(1.0);
	glPopMatrix();
	
}