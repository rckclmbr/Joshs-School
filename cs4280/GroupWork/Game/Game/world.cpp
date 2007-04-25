#include "world.h"


CWorld::CWorld()
{
	terrain = new CTerrain(32, 0.5);
}

CWorld::~CWorld()
{
	audioSystem->Shutdown();
	delete gui;
	delete terrain;
	terrain = NULL;

	gui = NULL;

	delete audioSystem;
	delete worldSound;
	audioSystem = NULL;
	worldSound = NULL;
}

CWorld::CWorld(CCamera *c)
{
	camera = c;
	terrain = new CTerrain(32, 1.0f);
	player = new CPlayer;

	audioSystem = new CAudioSystem;

	gui = new CGUI;

	gameDone = false;

	audioSystem->InitDirectXAudio(NULL); 

	player->AttachTo(terrain);
	player->SetCamera(camera);
	player->SetTerrain(terrain);

	worldSound = audioSystem->Create("Quake.wav", false);
	audioSystem->Play(worldSound, DMUS_SEG_REPEAT_INFINITE, true);
	
	player->SetAudioSystem(audioSystem);
	player->SetAudioSystem(player->audioSys);							// added by Lorin
	player->LoadAudio(player->audioSys, ".\\gunshot.wav", false);		// load rocket launcher sound. added by Lorin

	LoadWorld();
	timeStart = 300.0;			// 300 seconds = 5 minutes
	timeElapsed = 0.0;

	gui->SetCurrentTime(timeStart);
	gui->SetEnemiesLeft(numOgros + numSods + numCows + numMechs + numDragons + numDroids);
}

void CWorld::Animate(float deltaTime)
{
	//Todd Brown's Code Modifications
	TB_PlayerPosition.x = camera->position.x;
	TB_PlayerPosition.y = camera->position.z;
	TB_PlayerYaw = camera->yaw;
	//End Todd Brown's Code Modifications
	
	// Add hardwired 7.0f for player size
	//  Add player-> size back to camera position
	// set camera height based on player position on terrain
	camera->position.y = terrain->GetHeight(camera->position.x, camera->position.z) + player->size;	
	
	if (camera->position.x <= terrain->GetScanDepth())
		camera->position.x = terrain->GetScanDepth();
	if (camera->position.x >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.x = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();
	if (camera->position.z <= terrain->GetScanDepth())
		camera->position.z = terrain->GetScanDepth();
	if (camera->position.z >= terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth())
		camera->position.z = terrain->GetWidth()*terrain->GetMul() - terrain->GetScanDepth();

	terrain->Animate(deltaTime);   // animate terrain
	
	const type_info &ogro = typeid(COgroEnemy);  // get ogro typeid
	const type_info &sod = typeid(CSodEnemy);    // get sod typeid
	//new cow enemy
	const type_info &cow = typeid(CCowEnemy);
	//new mech enemy
	const type_info &mech = typeid(CMechEnemy);
	const type_info &droid = typeid(CDroidEnemy);
	const type_info &dragon = typeid(CDragonEnemy);

	numOgros = CountObjectTypes(ogro);           // count ogros
	TB_NumOgros = numOgros;
	numSods = CountObjectTypes(sod);             // count sods
	TB_NumSods = numSods;
	numCows = CountObjectTypes(cow);			// count cows
	TB_NumCows = numCows;
	numMechs = CountObjectTypes(mech);			// count mech
	TB_NumMechs = numMechs;
	numDroids = CountObjectTypes(droid);		// count droid
	TB_NumDroids = numDroids;

	numDragons = CountObjectTypes(droid);		// count droid
	TB_NumDragons = numDragons;
	
	gui->SetEnemiesLeft(numOgros + numSods + numCows + numMechs + numDroids + numDragons);
	gui->SetCurrentTime(timeStart - timeElapsed);

	if (!gameDone)
		timeElapsed += deltaTime;
	else
		timeElapsed = timeStart;
 


}

void CWorld::FadeScreen()
{
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_TEXTURE_2D);
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);
	glVertex3f(-5, -5, -3.0);
	glVertex3f(5, -5, -3.0);
	glVertex3f(5, 5, -3.0);
	glVertex3f(-5, 5, -3.0);
	glEnd();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);
	glPopMatrix();
}

void CWorld::SetScreen(int width, int height)
{
	screenWidth = width;
	screenHeight = height;
}

void CWorld::Draw(CCamera *camera)
{
	terrain->Draw(camera);
	gui->Draw();

	if (gameDone)
	{
		FadeScreen();
		if (numOgros + numSods + numCows + numMechs + numDroids + numDragons <= 0)
			gui->DrawWinner();
		else
			gui->DrawLoser();
	}
}

void CWorld::OnPrepare()
{
	glClearColor(terrain->fogColor[0], terrain->fogColor[1], terrain->fogColor[2], terrain->fogColor[3]);
	terrain->Prepare();

	if ((numOgros + numSods + numCows + numMechs + numDroids + numDragons<= 0) || (timeElapsed >= timeStart))
		gameDone = true;	
}


// LoadWorld()
// desc: initializes the world
void CWorld::LoadWorld()
{
	int enemyIdx = 0;
	int rndInt = 0;

	
	srand((unsigned int)time(NULL));
	
	rndInt = (rand() % (MAX_ENEMIES-3)) + 3;	// random # from 4 to MAX
	numOgros = numSods = numCows = numMechs = numDroids = numDragons = rndInt;
	

	//generate cows
	for (enemyIdx = 0; enemyIdx < numCows; enemyIdx++)
	{
		cowEnemy = new CCowEnemy;
		cowEnemy->AttachTo(terrain);
		cowEnemy->SetPlayer(player);
		cowEnemy->SetAudioSystem(audioSystem);
		cowEnemy->LoadAudio(audioSystem, "models\\Cow\\cow.wav", false);
		cowEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		cowEnemy->position.y = 0.0f;
		cowEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}
	
	//generate mechs
	for (enemyIdx = 0; enemyIdx < numMechs; enemyIdx++)
	{
		mechEnemy = new CMechEnemy;
		mechEnemy->AttachTo(terrain);
		mechEnemy->SetPlayer(player);
		mechEnemy->SetAudioSystem(audioSystem);
		mechEnemy->LoadAudio(audioSystem, "models\\mech\\enemy.wav", false);
		mechEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		mechEnemy->position.y = 0.0f;
		mechEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

	// generate ogros
	for (enemyIdx = 0; enemyIdx < numOgros; enemyIdx++)
	{
		ogroEnemy = new COgroEnemy;
		ogroEnemy->AttachTo(terrain);
		ogroEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		ogroEnemy->SetAudioSystem(audioSystem);
		ogroEnemy->LoadAudio(audioSystem, "models\\ogro\\ddeath.wav", false);
		ogroEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		ogroEnemy->position.y = 0.0f;
		ogroEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

	// generate sods
	for (enemyIdx = 0; enemyIdx < numSods; enemyIdx++)
	{
		sodEnemy = new CSodEnemy;
		sodEnemy->AttachTo(terrain);
		sodEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		sodEnemy->SetAudioSystem(audioSystem);
		sodEnemy->LoadAudio(audioSystem, "models\\sodf8\\creaturehit.wav", false);
		sodEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		sodEnemy->position.y = 0.0f;
		sodEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

	for (enemyIdx = 0; enemyIdx < numDroids; enemyIdx++)
	{
		droidEnemy = new CDroidEnemy;
		droidEnemy->AttachTo(terrain);
		droidEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		droidEnemy->SetAudioSystem(audioSystem);
		droidEnemy->LoadAudio(audioSystem, "models\\Droid\\death1.wav", false);
		droidEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		droidEnemy->position.y = 0.0f;
		droidEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

	for (enemyIdx = 0; enemyIdx < numDragons; enemyIdx++)
	{
		dragonEnemy = new CDragonEnemy;
		dragonEnemy->AttachTo(terrain);
		dragonEnemy->SetPlayer(player);
		// Phase 19 - Uncomment
		dragonEnemy->SetAudioSystem(audioSystem);
		dragonEnemy->LoadAudio(audioSystem, "models\\Dragon\\death1.wav", false);
		dragonEnemy->position.x = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
		dragonEnemy->position.y = 0.0f;
		dragonEnemy->position.z = (float)(rand() % (int)(terrain->GetWidth() * terrain->GetMul()));
	}

		
  // Phase 15 - End
}
// Phase 15 - Begin
// CountObjectTypes
// desc: counts the number of objects passed as classID in the hierarchy
int CWorld::CountObjectTypes(const type_info &classID)
{
	int count = 0;
	CObject *c1;
	CObject *c2;

	c1 = (CObject*)terrain->childNode;

	//Todd Brown's Code Modifications
	const type_info &ogro = typeid(COgroEnemy);  // get ogro typeid
	const type_info &sod = typeid(CSodEnemy);    // get sod typeid
	const type_info &cow = typeid(CCowEnemy);
	const type_info &mech = typeid(CMechEnemy);
	const type_info &droid = typeid(CDroidEnemy);
	const type_info &dragon = typeid(CDragonEnemy);
	int index = 0;
	if (classID == ogro)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_OgroPtr[x]=NULL;
	}
	if (classID == sod)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_SodPtr[x]=NULL;
	}
	if (classID == cow)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_CowPtr[x]=NULL;
	}
	if (classID == mech)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_MechPtr[x]=NULL;
	}
	if (classID == droid)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_DroidPtr[x]=NULL;
	}
	if (classID == dragon)
	{
		for (int x=0; x<MAX_ENEMIES; x++)
			TB_DragonPtr[x]=NULL;
	}
	//End Todd Brown's Code Modifications

	while (c1 != NULL)
	{
		c2 = c1;
		do
		{
			if (typeid(*c2) == classID)
			{
				if (classID == ogro)
				{
					TB_OgroPtr[index] = static_cast<COgroEnemy *>(c2);
					index ++;
				}
				if (classID == sod)
				{
					TB_SodPtr[index] = static_cast<CSodEnemy *>(c2);
					index ++;
				}
				if (classID == cow)
				{
					TB_CowPtr[index] = static_cast<CCowEnemy *>(c2);
					index ++;
				}
				if (classID == mech)
				{
					TB_MechPtr[index] = static_cast<CMechEnemy *>(c2);
					index ++;
				}
				if (classID == droid)
				{
					TB_DroidPtr[index] = static_cast<CDroidEnemy *>(c2);
					index ++;
				}
				if (classID == dragon)
				{
					TB_DragonPtr[index] = static_cast<CDragonEnemy *>(c2);
					index ++;
				}
				count++;
			}
			c2 = (CObject*)c2->nextNode;
		} while (!c2->IsFirstChild());
//      Phase 19 - Remove the following
//		count--;

		c1 = (CObject*)c1->childNode;
	}

	return count;
}
// Phase 15 - End
