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

Camera cam; // global camera object
bool toggle = false;
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
	case 'M':    fly = !fly;break; //To fly the camera--MUST BE DONE AT THE BEGINGING BEFORE MANUAL MOVEMENT
	//controls for continuous motion camera
	case 'w':	up = !up;break;
	case 's':	down = !down;break;
	case 'a':	rollleft = !rollleft;break;
	case 'd':	rollright = !rollright;break;
  }
	glutPostRedisplay(); // draw it again
}
//<<<<<<<<<<<<<<<<<<<<<<<< mySpecialKeyboard >>>>>>>>>>>>>>>>>>>>>>
void mySpecialKeys(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		{
			foward = !foward;
			break;
		}
	case GLUT_KEY_DOWN:
		{
			back = !back;
			break;
		}
	case GLUT_KEY_LEFT:
		{
			left1 = !left1;
			break;
		}
	case GLUT_KEY_RIGHT:
		{
			right1 = !right1;
			break;
		}
	default:
		{}
	}
	glutPostRedisplay();
}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f); // set color of stuff 
	glutWireTeapot(1.0); // draw the teapot
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
		
		//cam.roll(.1);
		//cam.slide(-0.01,0,0);

		//cam.pitch(1.0);
		//cam.slide(0,0.1,0);
	}
	//allows for continous motion in the idle state
	if(foward)
		cam.slide(0,0,-0.1);
	if(back)
		cam.slide(0,0,.1);
	if(left1)
		cam.yaw(-.5);
	if(right1)
		cam.yaw(.5);
	if(up)
		cam.pitch(-.5);
	if(down)
		cam.pitch(.5);
	if(rollleft)
		cam.roll(.5);
	if(rollright)
		cam.roll(-.5);
	glutPostRedisplay();
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffering
	glutInitWindowSize(640,480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("fly a camera around a teapot");
	glutKeyboardFunc(myKeyboard);
	glutSpecialFunc(mySpecialKeys);
	glutDisplayFunc(myDisplay);
	glutIdleFunc(Idle);
	glClearColor(1.0f,1.0f,1.0f,0.0f);  // background is white 
    glViewport(0, 0, 640, 480);
	cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);
	cam.set(0, 2, 7, 0, 0, 0, 0, 1, 0); // make the initial camera
	glutMainLoop();
}

