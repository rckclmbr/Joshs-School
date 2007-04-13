#ifndef __COW_H
#define __COW_H

/*


*/

#include "enemy.h"
#include "sod.h"
#include "ogro.h"
#include <time.h>

class CCowEnemy : public CEnemy
{
private:
	
protected:
	void OnProcessAI();
	void OnCollision(CObject *collisionObject);
	void OnPrepare();

public:
	CAudioSystem *audioSys;
	CCowEnemy() { Load(); }
	CCowEnemy(float x, float z) { position.x = x; position.z = z; Load(); }
	~CCowEnemy() {}

	void Load();
};


#endif
