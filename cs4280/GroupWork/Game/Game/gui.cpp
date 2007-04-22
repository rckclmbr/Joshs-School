#include "gui.h"
#include <math.h>
#include "world.h"

CGUI::CGUI()
{
	minutesLeft = secondsLeft = enemiesLeft = 0;
	font = new CFont("Arial", 16);
	crosshair = new CFont("Courier New", 28);
	endText = new CFont("Arial", 40);
	enemy1 = new CFont("Courier New", 22);
	enemy2 = new CFont("Courier New", 22);
	enemy3 = new CFont("Courier New", 22);
	enemy4 = new CFont("Courier New", 22);
	enemy5 = new CFont("Courier New", 22);
	player1 = new CFont("Courier New", 22);
	keyFont = new CFont("Courier New", 20);
}

CGUI::~CGUI()
{
	font->ClearFont();
	crosshair->ClearFont();
	endText->ClearFont();
	enemy1->ClearFont();
	enemy2->ClearFont();
	player1->ClearFont();
	delete font;
	delete crosshair;
	delete endText;
	delete enemy1;
	delete enemy2;
	delete enemy3;
	delete enemy4;
	delete enemy5;
	delete player1;
}

void CGUI::SetCurrentTime(float timeLeft)
{
	// timeLeft is in seconds

	minutesLeft = (int)(timeLeft / 60.0);	// 60 seconds in 1 minute
	secondsLeft = (int)floor(timeLeft) % 60;
	millisecondsLeft = static_cast<int>((timeLeft - (float)floor(timeLeft)) * 1000);
}

void CGUI::SetEnemiesLeft(int eLeft)
{
	enemiesLeft = eLeft;
}

void CGUI::DrawWinner()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.15f, -0.1f);
	endText->SetRGBA(0.3f, 1.0f, 0.3f, 0.8f);
	endText->Print("YOU WIN!");

	endText->SetPos3D(-0.5f, -0.2f, -0.1f);
	endText->SetRGBA(1.0f, 1.0f, 1.0f, 0.8f);
	endText->Print("Press the ESC key to exit");
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void CGUI::DrawLoser()
{
	glDisable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	endText->SetPos3D(-0.25f, 0.15f, -0.1f);
	endText->SetRGBA(1.0f, 0.3f, 0.3f, 0.8f);
	endText->Print("YOU LOSE!");

	endText->SetPos3D(-0.5f, -0.2f, -0.1f);
	endText->SetRGBA(1.0f, 1.0f, 1.0f, 0.8f);
	endText->Print("Press the ESC key to exit");
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}

void CGUI::Draw()
{
	glDisable(GL_TEXTURE_2D);
	font->SetPos3D(2.5f, 2.7f, -5.0f);
	font->SetRGB(0.2f, 0.0f, 1.0f);
	
	if (secondsLeft < 10)
	{
		if (millisecondsLeft < 10)
			font->Print("Time: %d:0%d.0%d", minutesLeft, secondsLeft, millisecondsLeft);
		else
			font->Print("Time: %d:0%d.%d", minutesLeft, secondsLeft, millisecondsLeft);
	}
	else
	{
		if (millisecondsLeft < 10)
			font->Print("Time: %d:%d.0%d", minutesLeft, secondsLeft, millisecondsLeft);
		else
			font->Print("Time: %d:%d.%d", minutesLeft, secondsLeft, millisecondsLeft);
	}

	font->SetPos3D(2.5f, 2.5f, -5.0f);
	font->Print("Enemies: %d", enemiesLeft);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	crosshair->SetRGBA(1.0f, 0.1f, 0.1f, 0.7f);
	crosshair->SetPos3D(-0.03f, -0.03f, -5.0f);
	crosshair->Print("+");

	if (TB_MapEnable)
	{
		//my Routine
		player1->SetRGBA(1.0f, 1.0f, 1.0f, 0.8f);
		player1->SetPos3D(static_cast<GLfloat>(-1.*((TB_PlayerPosition.x/800.)+2.+0.05)), static_cast<GLfloat>((TB_PlayerPosition.y/800.)+1.-0.06), -5.f);
		player1->Print("+");
		//
		enemy1->SetRGBA(0.14f, 0.89f, 0.04f, 0.8f);
		for (int x=0; x<MAX_ENEMIES; x++)
		{
			if (TB_OgroPtr[x] != NULL)
			{
				enemy1->SetPos3D(static_cast<GLfloat>(-1.*((TB_OgroPtr[x]->position.x/800.)+2.+0.03)), static_cast<GLfloat>((TB_OgroPtr[x]->position.z/800.)+1.-0.06), -5.f);
				enemy1->Print("+");
			}
		}
		//
		enemy2->SetRGBA(0.02f, 0.07f, 0.92f, 0.8f);
		for (int x=0; x<MAX_ENEMIES; x++)
		{
			if (TB_SodPtr[x] != NULL)
			{
				enemy2->SetPos3D(static_cast<GLfloat>(-1.*((TB_SodPtr[x]->position.x/800.)+2.+0.03)), static_cast<GLfloat>((TB_SodPtr[x]->position.z/800.)+1.-0.06), -5.f);
				enemy2->Print("+");
			}
		}
		//
		enemy3->SetRGBA(0.93f, 0.16f, 0.01f, 0.8f);
		for (int x=0; x<MAX_ENEMIES; x++)
		{
			if (TB_CowPtr[x] != NULL)
			{
				enemy3->SetPos3D(static_cast<GLfloat>(-1.*((TB_CowPtr[x]->position.x/800.)+2.+0.03)), static_cast<GLfloat>((TB_CowPtr[x]->position.z/800.)+1.-0.06), -5.f);
				enemy3->Print("+");
			}
		}
		//
		enemy4->SetRGBA(0.93f, 0.89f, 0.0f, 0.8f);
		for (int x=0; x<MAX_ENEMIES; x++)
		{
			if (TB_MechPtr[x] != NULL)
			{
				enemy4->SetPos3D(static_cast<GLfloat>(-1.*((TB_MechPtr[x]->position.x/800.)+2.+0.03)), static_cast<GLfloat>((TB_MechPtr[x]->position.z/800.)+1.-0.06), -5.f);
				enemy4->Print("+");
			}
		}
		//
		enemy5->SetRGBA(1.00f, 0.50f, 0.0f, 0.8f);
		for (int x=0; x<MAX_ENEMIES; x++)
		{
			if (TB_DroidPtr[x] != NULL)
			{
				enemy5->SetPos3D(static_cast<GLfloat>(-1.*((TB_DroidPtr[x]->position.x/800.)+2.+0.03)), static_cast<GLfloat>((TB_DroidPtr[x]->position.z/800.)+1.-0.06), -5.f);
				enemy5->Print("+");
			}
		}
	}

	if (TB_KeyEnable)
	{
		keyFont->SetRGBA(0.14f, 0.89f, 0.04f, 0.8f);
		keyFont->SetPos3D(-2.f, 2.75f, -5.f);
		keyFont->Print("Num Ogros Left : %d", TB_NumOgros);
		//
		keyFont->SetRGBA(0.02f, 0.07f, 0.92f, 0.8f);
		keyFont->SetPos3D(-2.f, 2.55f, -5.f);
		keyFont->Print("Num Sods Left  : %d", TB_NumSods);
		//
		keyFont->SetRGBA(0.93f, 0.16f, 0.01f, 0.8f);
		keyFont->SetPos3D(-2.f, 2.35f, -5.f);
		keyFont->Print("Num Cows Left  : %d", TB_NumCows);
		//
		keyFont->SetRGBA(0.93f, 0.89f, 0.0f, 0.8f);
		keyFont->SetPos3D(-2.f, 2.15f, -5.f);
		keyFont->Print("Num Mechs Left : %d", TB_NumMechs);
		//
		keyFont->SetRGBA(1.00f, 0.50f, 0.0f, 0.8f);
		keyFont->SetPos3D(-2.f, 1.95f, -5.f);
		keyFont->Print("Num Droids Left: %d", TB_NumDroids);
	}
	
	glDisable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
}