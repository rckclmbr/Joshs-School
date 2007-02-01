#if defined(_WIN32)
#include <windows.h>
#endif

#if defined(__APPLE__) || defined(MACOSX)

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>

#else

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#endif

#include <stdlib.h>

