#include "includes/header.h"
#include "includes/Camera.h"

Camera cam; // global camera object

//<<<<<<<<<<<<<<<<<<<<<<<< myKeyboard >>>>>>>>>>>>>>>>>>>>>>
void myKeyboard(unsigned char key, int x, int y)
{
  switch(key)
  {	
	// controls for camera
	case 'R': cam.roll(1.); break; 			//roll camera CW	
	case 'R'-64: cam.roll(-1.);break; 		//roll camera CCW
	case 'P': cam.pitch(1.);break; 			//pitch forward
	case 'P'-64: cam.pitch(-1.); break; 		//pitch back
	case 'Y': cam.yaw(-1.);break; 			//yaw left
	case 'Y'-64: cam.yaw(1.); break; 		//yaw right
	case 'F': cam.slide(0,0,-0.2);break; 		//forward
	case 'F'-64: cam.slide(0,0,0.2); break; 	//back
	case 'U': cam.slide(0,0.2,0); break; 		//up
	case 'U'-64: cam.slide(0,-0.2,0);break; 	//down
	case 'L': cam.slide(-0.2,0,0);break; 		//left
	case 'L'-64: cam.slide(0.2,0,0); break; 	//right
  }
	glutPostRedisplay(); // draw it again
}
//<<<<<<<<<<<<<<<<<<<<<<< myDisplay >>>>>>>>>>>>>>>>>>>>>>>>>>
void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0f,0.0f,0.0f);			// set color of stuff 
	glutWireTeapot(1.0); // draw the teapot
	glutSwapBuffers(); // display the screen just made
} 
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // double buffering
	glutInitWindowSize(640,480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("fly a camera around a teapot");
	glutKeyboardFunc(myKeyboard);
	glutDisplayFunc(myDisplay);
	glClearColor(1.0f,1.0f,1.0f,0.0f);  // background is white 
	
	glViewport(0, 0, 640, 480);
	cam.setShape(30.0f, 64.0f/48.0f, 0.5f, 50.0f);
	cam.set(4, 4, 4, 0, 0, 0, 0, 1, 0); // make the initial camera
	glutMainLoop();
	
	return 0;
}
