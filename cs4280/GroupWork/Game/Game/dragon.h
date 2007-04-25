#ifndef __DRAGON_H
#define __DRAGON_H

/*


*/

#include "enemy.h"
#include "sod.h"
#include "ogro.h"
#include <time.h>

class CDragonEnemy : public CEnemy
{
private:
	
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

public:
	CAudioSystem *audioSys;
	CDragonEnemy() { Load(); }
	CDragonEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CDragonEnemy() {}

	void Load();
};


#endif