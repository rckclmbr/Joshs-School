#ifndef __DROID_H
#define __DROID_H

/*


*/

#include "enemy.h"
#include "sod.h"
#include "ogro.h"
#include <time.h>

class CDroidEnemy : public CEnemy
{
private:
	
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

public:
	CAudioSystem *audioSys;
	CDroidEnemy() { Load(); }
	CDroidEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CDroidEnemy() {}

	void Load();
};


#endif
