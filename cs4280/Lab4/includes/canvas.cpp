Canvas::Canvas(int width, int height, char* windowTitle)
{
	char *argv[1]; 				//dummy argument list for glutInit()
	char dummyString [8 ]; 
	argv[0] = dummyString; 			//hook up the pointer
	int argc =1; 				//to satisfy glutInit()
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(20, 20);
	glutCreateWindow(windowTitle); 		//open the screen window
	setWindow(0, (float)width, 0, (float)height); //default world window
	setViewport(0, width, 0, height); 	//default viewport
	CP.set(0.0f, 0.0f); 			//initialize the CP to (0,0)
	CD = 0;					//initialize CD to 0
}

void Canvas::setWindow (float l,float r,float b,float t)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D((GLdouble)l, (GLdouble)r, (GLdouble)b, (GLdouble)t);
	window.set(l, r, b, t);
} 

void Canvas::setViewport (int l, int r, int b, int t)
{
	glViewport((GLint)l, (GLint)b, (GLint)(r - l), (GLint)(t - b));
	viewport.set(l, r, b, t);
}

void Canvas::setBackgroundColor(float r, float g, float b) {
	glClearColor(r,g,b,1);
}

void Canvas::setColor(float r, float g, float b) {
	glColor3f(r,g,b);
}

void Canvas::clearScreen() {
	glClear(GL_COLOR_BUFFER_BIT);
}

void Canvas::moveTo(float x, float y)
{
	CP.set(x, y);
} 

void Canvas::moveTo(Point2 p)
{
	CP.set(p.getX(), p.getY());
}

void Canvas::lineTo (float x, float y)
{
	glBegin (GL_LINES);
	        glVertex2f ((GLfloat)CP.getX(), (GLfloat)CP.getY());
	        glVertex2f ((GLfloat)x, (GLfloat)y); //draw the line
	glEnd();
	CP.set (x, y);//update the CP
	glFlush();
}
 
void Canvas::lineTo (Point2 p)
{
	glBegin (GL_LINES);
	        glVertex2f ((GLfloat)CP.getX(), (GLfloat)CP.getY());
	        glVertex2f ((GLfloat)p.getX(), (GLfloat)p.getY()); //draw the line
	glEnd();
	CP.set (p.getX(), p.getY()); //update the CP
	glFlush();
}


void Canvas::moveRel(float dx, float dy)
{
	CP.set(CP.getX() + dx, CP.getY() + dy);
} 

void Canvas::lineRel(float dx, float dy)
{
	float x = CP.getX() + dx, y = CP.getY() + dy; 
	lineTo(x, y);
	CP.set(x, y);
}

void Canvas::turnTo(float angle) 
{
	CD = angle;
}

void Canvas::turn(float angle) 
{
	CD += angle;
}

void Canvas::forward(float dist, int isVisible) 
{
	const float RadPerDeg = 0.017453393;
	float x = CP.getX() + dist * cos(RadPerDeg * CD);
	float y = CP.getY() + dist * sin(RadPerDeg * CD);
	if(isVisible)
		lineTo(x,y);
	else
		moveTo(x,y);
}
