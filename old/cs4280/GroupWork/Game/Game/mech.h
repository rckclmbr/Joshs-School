#ifndef __MECH_H
#define __MECH_H

/*


*/

#include "enemy.h"
#include "sod.h"
#include "ogro.h"
#include "cow.h"
#include <time.h>

class CMechEnemy : public CEnemy
{
private:
	
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

public:
	CAudioSystem *audioSys;
	CMechEnemy() { Load(); }
	CMechEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CMechEnemy() {}

	void Load();
};


#endif
