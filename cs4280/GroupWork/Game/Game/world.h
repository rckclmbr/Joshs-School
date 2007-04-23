#ifndef __WORLD_H
#define __WORLD_H

/*
	WORLD.H

  	The CWorld class

	Description: The CWorld class represents the game world
			   of the engine. All objects, the terrain,
			   audio system, ambient world music and sound,
			   and the camera are held here.


*/

#include <typeinfo.h>
#include "gui.h"
#include "player.h"
#include "sod.h"
#include "ogro.h"
#include "cow.h"
#include "mech.h"
#include "droid.h"
#include "entity.h"
#include "md2.h"
#include "object.h"
#include "camera.h"
#include "terrain.h"
#include "audiosystem.h"
#include "tree.h"

#define MAX_ENEMIES 5

//Todd Brown's Code Modification
struct TB_PositionInfo
{
	float x;
	float y;
};
__declspec(selectany) TB_PositionInfo TB_PlayerPosition;
__declspec(selectany) float TB_PlayerYaw;
__declspec(selectany) COgroEnemy * TB_OgroPtr[MAX_ENEMIES];
__declspec(selectany) CSodEnemy * TB_SodPtr[MAX_ENEMIES];
__declspec(selectany) CCowEnemy * TB_CowPtr[MAX_ENEMIES];
__declspec(selectany) CMechEnemy * TB_MechPtr[MAX_ENEMIES];
__declspec(selectany) CDroidEnemy * TB_DroidPtr[MAX_ENEMIES];
__declspec(selectany) bool TB_MapEnable = false;
__declspec(selectany) bool TB_KeyEnable = false;
__declspec(selectany) int TB_NumOgros;
__declspec(selectany) int TB_NumSods;
__declspec(selectany) int TB_NumCows;
__declspec(selectany) int TB_NumMechs;
__declspec(selectany) int TB_NumDroids;
//End Todd Brown's Code Modification

class CWorld
{
private:
	// Begin - Phase 15
	int numOgros, numSods, numCows, numMechs, numDroids;
	// End - Phase 15
	int screenWidth, screenHeight;
	bool gameDone;
	
	CAudioSystem *audioSys;

protected:
	void OnAnimate(float deltaTime);
	void OnDraw(CCamera *camera);
	void OnPrepare();

public:
	
	HWND hwnd;

	CTerrain *terrain;
	CCamera *camera;			// the camera
	CPlayer *player;
	CAudioSystem *audioSystem;
	CAudio *worldSound;
	CGUI *gui;
	COgroEnemy *ogroEnemy;
	CSodEnemy *sodEnemy;
	CCowEnemy *cowEnemy;
	CMechEnemy *mechEnemy;
	CDroidEnemy *droidEnemy;
	float timeStart;
	float timeElapsed;

	CWorld();
	CWorld(CCamera *c);
	~CWorld();

	// initialize terrain, load objects and put in container
	void LoadWorld();
	void UnloadWorld();

	int CountObjectTypes(const type_info &classID);

	// do physics calculations for all objects in the world
	// including collisions
	void Animate(float deltaTime);

	// render all objects in the world
	void Draw(CCamera *camera);
	void Prepare() { OnPrepare(); }

	void FadeScreen();
	void SetScreen(int width, int height);

	bool IsGameDone() 
	{ 
		
		return false; 
	}
	void QuitGame() { gameDone = true; }
	int GetOgros() { return numOgros; }
	int GetSods() { return numSods; }
	int GetCows() { return numCows; }
	int GetMechs() { return numMechs; }
	int GetDroids() { return numDroids; }
};


#endif