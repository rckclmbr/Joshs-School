#ifndef __GL_COMPONENT
#define __GL_COMPONENT

//#define PI 3.14159
#define TWO_PI PI*2.0
#define HALF_PI PI/2.0

// Begin - Phase 5
#include "camera.h"
// remove above definition of PI - already defined in vector.h
// End - Phase 5

// Begin - Phase 11
#include "world.h"
// remove above definition of PI - already defined in vector.h
// End - Phase 11
#include "audiosystem.h"
class OGLWindow
{
private:
	int m_windowWidth;
	int m_windowHeight;
	//CAudioSystem *audioSys;
	float m_angle;
	CCamera *gameCamera;

	CCamera *OnGetCamera() { return gameCamera; }
	CWorld *gameWorld;
	CWorld *OnGetWorld() { return gameWorld; }

public:
	OGLWindow();
	virtual ~OGLWindow();

	bool Init();
	bool Shutdown();

	void SetupProjection(int width, int height);
	void Prepare();
	void Render(float deltaTime);
	int mouseX;
	int mouseY;
	float mouseSensitivity;
	int GetMouseX(LPARAM lParam);		// get true mouse coordinates
	int GetMouseY(LPARAM lParam);
	void OnMouseMove(int x, int y);
	void OnKeyDown(int nVirtKey); 
	void OnMouseDownL(int x, int y);
};

#endif