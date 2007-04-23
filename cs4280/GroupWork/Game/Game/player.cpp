#include "player.h"

// Phase 14 - Take out until Rocket is introduced
// Phase 16 - Uncomment
void CPlayer::FireWeapon()
{
	// use camera->lookAt vector and multiply
	// this lookAt vector by the ammo's speed
	// to get the ammo velocity vector.
	// create the new ammo and attach it to
	// the world. fire the ammo

	CRocket *newRocket = new CRocket;

	newRocket->pitch = (camera->pitch - 10);
	newRocket->direction = direction;
	newRocket->position = position;
	newRocket->forward = camera->lookAt.UnitVector();
// Phase 19 - Uncomment the following
	newRocket->SetAudioSystem(audioSys);
	newRocket->LoadAudio(audioSys, "explode.wav", false);
	newRocket->AttachTo(terrain);
}

void CPlayer::LoadAudio(CAudioSystem *audioSystem, char *filename, bool is3DSound)
{
	if (rocketSound != NULL)
	{
		delete [] rocketSound;
		rocketSound = new CAudio;
	}

	if (audioSystem != NULL)
		rocketSound = audioSystem->Create(filename, is3DSound);
	else
	{
		delete [] rocketSound;
		rocketSound = NULL;
	}
}

