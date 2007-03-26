#include "Camera.h"

Camera cam; // global camera object
//material struct
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
	52.0
};
materialStruct whiteShiney = {
	{1,0,1,1},
	{1,0,1,1},
	{1,1,1,1},
	50
};

//assign them to faces
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
	case 'U':	cam.slide(0,.2,0); break;
	case 'U'-64:	cam.slide(0,-.2,0); break;
	case 'L':	cam.slide(.2,0,0);	break;
	case 'L'-64: cam.slide(-.2,0,0); break;
	case 'R':    cam.roll(-1.);break; // roll camera CW
	case 'R'-64: cam.roll(1.); break; //roll camera CCW	
	case 'P':	cam.pitch(1.); break;
	case 'P'-64:	cam.pitch(-1.); break;
	case 'Y':	cam.yaw(1.); break;
	case 'Y'-64: cam.yaw(-1.); break;
	default:
		{
		break;
		}
	// add roll and yaw controls
  }
	glutPostRedisplay(); // draw it again
}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);	// set color of stuff 
//make things solid instead of crazy
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
//create light source and position
	GLfloat light_pos1[] = {5.0,5.0,5.0,0.0};
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0,GL_POSITION,light_pos1);
	
	//grid
	for(int x = -100; x<100;x++)
	{
		glBegin(GL_LINES);
			glVertex3d(x,0,100); glVertex3d(x,0,-100);
		glEnd();
		glBegin(GL_LINES);
			glVertex3d(100,0,x); glVertex3d(-100,0,x);
		glEnd();
	}

	
//donut
glPushMatrix();
	materials(&redPlastic);
	glutSolidTorus(.5,1,30,50);
glPopMatrix();
//octo shape
glPushMatrix();
	materials(&brassMaterials);
	glTranslatef(1,0,2);
	glutSolidOctahedron();
glPopMatrix();
//another donut
glPushMatrix();
	glTranslatef(3,1,1);
	glRotatef(45,0,1,0);
	glutSolidTorus(.2,1,20,20);
glPopMatrix();
//cone
glPushMatrix();
	materials(&whiteShiney);
	glTranslatef(-2,3,0);
	glRotatef(45,1,0,0);
	glutSolidCone(1,2,10,15);
glPopMatrix();

materials(&redPlastic);
	glutSwapBuffers(); // display the screen just made
} 
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); // double buffering
	glutInitWindowSize(640,480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("fly a camera around a teapot");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glClearColor(1.0f,1.0f,1.0f,0.0f);  // background is white 
	
	glViewport(0, 0, 640, 480);
	cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);
	cam.set(0, 2, 10, 0, 0, 0, 0, 1, 0); // make the initial camera
	glutMainLoop();
}
