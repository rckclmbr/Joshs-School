#ifndef __GUI_H
#define __GUI_H

#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

/*
	
	GUI.H
	The GUI class interface
	OpenGL Game Programming
	Author: Kevin Hawkins
	Date: 4/2/2001
	Description:

*/

#include <windows.h>
#include "font.h"
#include "texture.h"

class CGUI
{
private:
	int minutesLeft, secondsLeft, millisecondsLeft;
	int enemiesLeft;

	CFont *font;
	CFont *keyFont;
	CFont *crosshair;
	CFont *endText;
	CFont *player1;
	CFont *enemy1;
	CFont *enemy2;
	CFont *enemy3;
	CFont *enemy4;
	CFont *enemy5;

public:
	CGUI();
	~CGUI();

	void SetCurrentTime(float timeLeft);
	void SetEnemiesLeft(int eLeft);
	void Draw();
	void Animate(float deltaTime);

	void DrawWinner();
	void DrawLoser();
};


#endif