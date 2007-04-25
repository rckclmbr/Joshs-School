#ifdef _WINDOWS
#include <windows.h>
#endif

#include <gl/Gl.h>
#include <gl/Glu.h>
#include <math.h>
#include "OGLWindow.h"

// disable implicit float-double casting
#pragma warning(disable:4305)

OGLWindow::OGLWindow()
{
}

OGLWindow::~OGLWindow()
{
}

bool OGLWindow::Init()
{   
    // clear to black background
    glClearColor(0.0, 0.0, 0.0, 0.0);

	mouseSensitivity = 8.0f;
	
    m_angle = 0.0f;

	gameCamera = new CCamera;

	gameWorld = new CWorld(gameCamera);

    return true;
}

bool OGLWindow::Shutdown()
{

	delete gameWorld;

	delete gameCamera;
	gameWorld = NULL;
	gameCamera = NULL;

    return true;
}

void OGLWindow::SetupProjection(int width, int height)
{
    if (height == 0)                    // don't want a divide by zero
    {
        height = 1;                 
    }

    glViewport(0, 0, width, height);        // reset the viewport to new dimensions
    glMatrixMode(GL_PROJECTION);            // set projection matrix current matrix
    glLoadIdentity();                       // reset projection matrix

    // calculate aspect ratio of window
    gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,1.0f,1000.0f);

    glMatrixMode(GL_MODELVIEW);             // set modelview matrix
    glLoadIdentity();                       // reset modelview matrix

    m_windowWidth = width;
    m_windowHeight = height;
}
void OGLWindow::Prepare()
{
	// clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);     
//	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
    m_angle += 0.1f;
}
// GetMouseX()
// desc: get mouse cursor position in window
int OGLWindow::GetMouseX(LPARAM lParam)
{
	return LOWORD(lParam);
}

// GetMouseY()
// desc: get mouse cursor position in window
int OGLWindow::GetMouseY(LPARAM lParam)
{
	return HIWORD(lParam);
}

void OGLWindow::OnMouseMove(int x, int y)
{
	// Update to azimuth and pitch control
	static float oldX;
	static float oldY;
	float mX, mY;
	float dx, dy;  // changes in mouse position

	int sizeX = this->m_windowWidth; // Used when controls are pegged
	int sizeY = this->m_windowHeight;

	mX = (float)x;
	mY = (float)y;

	dx = mX - oldX;
	dy = mY - oldY;

	//Add gameDone logic
	if (!gameWorld->IsGameDone())
	{
	// Areas on screen where directional movement is pegged
	if( mX < 30)
		gameCamera->yaw -= 1.0f*mouseSensitivity;
	if( mX > sizeX - 30)
		gameCamera->yaw += 1.0f*mouseSensitivity;
	if( mY < 30)
		gameCamera->pitch += 1.0f*mouseSensitivity;
	if( mY > sizeY - 30)
		gameCamera->pitch -= 1.0f*mouseSensitivity;


	if (dx < 0)
		gameCamera->yaw -= 0.25f*mouseSensitivity;
	if (dx > 0)
		gameCamera->yaw += 0.25f*mouseSensitivity;
	if (dy < 0)
		gameCamera->pitch += 0.25f*mouseSensitivity;
	if (dy > 0)
		gameCamera->pitch -= 0.25f*mouseSensitivity;

	oldX = mX;
	oldY = mY;
	}
}

void OGLWindow::OnKeyDown(int nVirtKey)
{
	// Add gameDone logic
	if (!gameWorld->IsGameDone())
	{
		switch (nVirtKey)
		{
		case VK_UP:

		// buttons 1 - 5 change the terrain texture.  added by Lorin
		case '1':	// green terrain
			gameWorld->terrain->iTex = 0;
			gameWorld->terrain->BuildTerrain(256, .5f);
			break;
		case '2':	// dessert terrain
			gameWorld->terrain->iTex = 1;
			gameWorld->terrain->BuildTerrain(256, .5f);
			break;
		case '3':	// snow terrain
			gameWorld->terrain->iTex = 2;
			gameWorld->terrain->BuildTerrain(256, .5f);
			break;
		case '4':	// snow terrain
			gameWorld->terrain->iTex = 3;
			gameWorld->terrain->BuildTerrain(256, .5f);
			break;
		case '5':	// snow terrain
			gameWorld->terrain->iTex = 4;
			gameWorld->terrain->BuildTerrain(256, .5f);
			break;
		// buttons 1-8 change the background sound.  added by Lorin
		case '6':
			gameWorld->worldSound = gameWorld->audioSystem->Create("Ambient.wav", false);
			gameWorld->audioSystem->Play(gameWorld->worldSound, DMUS_SEG_REPEAT_INFINITE, true);
			break;
		case '7':
			gameWorld->worldSound = gameWorld->audioSystem->Create("Quake.wav", false);
			gameWorld->audioSystem->Play(gameWorld->worldSound, DMUS_SEG_REPEAT_INFINITE, true);
			break;
		case '8':
			gameWorld->worldSound = gameWorld->audioSystem->Create("rock.wav", false);
			gameWorld->audioSystem->Play(gameWorld->worldSound, DMUS_SEG_REPEAT_INFINITE, true);
			break;
		case 87:
			gameCamera->velocity += CVector(0,0,2.0);
			break;
		case VK_DOWN:
		case 83:
			gameCamera->velocity += CVector(0,0,-2.0);
			break;
		case VK_RIGHT:
		case 68:
			gameCamera->velocity += CVector(1.0, 0.0, 0.0);
			break;
		case VK_LEFT:
		case 65:
			gameCamera->velocity += CVector(-1.0, 0.0, 0.0);
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			if (MessageBox(NULL, "Do you want to quit?", "Quit?", MB_ICONQUESTION|MB_YESNO)==IDYES) // added by Lorin
			{
				exit(0);  //kill game
			}
			break;
		case VK_ADD:
			mouseSensitivity += 0.05f;
			break;
		case VK_SUBTRACT:
			mouseSensitivity -= 0.05f;
			if (mouseSensitivity < 0.05)
				mouseSensitivity = 0.05;
			break;
		case 77:
			TB_MapEnable = !TB_MapEnable;
			break;
		case 75:
			TB_KeyEnable = !TB_KeyEnable;
			break;
		case 70: // F Pressed
			gameWorld->gui->ToggleFPS();
			break;
		default:
			break;
		}
	}
	else
	{
		if (nVirtKey == VK_ESCAPE)
		{
			if (MessageBox(NULL, "Do you want to quit?", "Quit?", MB_ICONQUESTION|MB_YESNO)==IDYES) // added by Lorin
			{
				exit(0);  //kill game
			}
		}
	}
}

void OGLWindow::OnMouseDownL(int x, int y) 
{
	
	if (!gameWorld->IsGameDone())
	{	
		gameWorld->player->audioSys->Play(gameWorld->player->rocketSound, 0, false);	// play rocket launcher fire sound.  Added by Lorin
		gameWorld->camera->pitch += 10;		//simulate recoil.  added by Lorin
		gameWorld->player->FireWeapon();		
	}
}

void OGLWindow::Render(float deltaTime)
{
	CCamera *camera = OnGetCamera();
	CWorld *world = OnGetWorld();

	world->Prepare();

	if (TB_MapEnable)
	{
		glDisable(GL_TEXTURE_2D);
		glColor4f(1.f, 1.f, 1.f, 0.f);
		glPushMatrix();
		glTranslatef(static_cast<GLfloat>(-1.*((TB_PlayerPosition.x/800.)+2.)), static_cast<GLfloat>((TB_PlayerPosition.y/800.)+1.f), -1.f);
		glRotatef(-TB_PlayerYaw, 0.0, 0.0, 1.0);
		glBegin(GL_LINES);
			glVertex3f(0.0, 0.0, -5.0);
			glVertex3f(-.2, 0.0, -5.0);
		glEnd();
		glPopMatrix();
		//
		glPushMatrix();
		glTranslatef(0.0, 0.0, -5.0f);
		glColor4f(0.f, 0.f, 0.f, 0.f);
		glBegin(GL_POLYGON);
			glVertex3f(-4.f, 3.f, -1.f);
			glVertex3f(-4.f, 1.f, -1.f);
			glVertex3f(-2.f, 1.f, -1.f);
			glVertex3f(-2.f, 3.f, -1.f);
		glEnd();
		glEnable(GL_TEXTURE_2D);
		glPopMatrix();
	}
	//change parameter to deltaTime
	camera->Animate(deltaTime);

	//change parameter to deltaTime
	world->Animate(deltaTime);
	world->Draw(camera);
}

