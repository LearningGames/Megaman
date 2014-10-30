#include "cGame.h"
#include "Globals.h";



cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}

bool cGame::Init()
{
	bool res=true;
	if (level == 0) level = 1;
	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization

	res = Data.LoadImage(IMG_MENU, "menu.png", GL_RGBA);
	if(!res) return false;

	res = Data.LoadImage(IMG_BLOCKS,"tile01.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(level);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"megaman.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(35,35);
	Player.SetTile(189, 4);
	Player.SetWidthHeight(35,35);
	Player.SetState(STATE_LOOKRIGHT);


	//Shot Initialization
	res = Data.LoadImage(IMG_SHOTRIGHT, "shootRight.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHOTLEFT, "shootLeft.png", GL_RGBA);
	if (!res) return false;
	Player.SetShotDimensions(20, 26);
	
	//Barra vida initialization
	res = Data.LoadImage(IMG_GUI_MEGA, "guimega.png", GL_RGBA);
	Player.SetLiveBar(80, 16);



	//Monster initialization
	res = Data.LoadImage(IMG_MONSTER, "megaman.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HELISHOT, "helishot.png", GL_RGBA);
	if (!res) return false;
	InitEnemies(level);
	res = Data.LoadImage(IMG_BOSS1, "boss1.png", GL_RGBA);
	InitEnemies2(level);
	//res = Data.LoadImage(IMG_PLAYER, "boss1.png", GL_RGBA);
	if (!res) return false;
	InitBoss();

	return res;
}

void cGame::InitBoss() {
	BurstMan.SetWidthHeight(54, 72);
	BurstMan.SetTile(194, 4);
	BurstMan.SetWidthHeight(54, 72);
	BurstMan.SetState(STATE_LOOKLEFT);
	BurstMan.SetShotDimensions(20, 26);
}

void cGame::InitEnemies(int level) {
	if (level == 1) {
		//First Monster
		cEnemy Monster = cEnemy();
		Monster.SetWidthHeight(35, 35);
		Monster.SetTile(16, 6);
		Monster.SetState(STATE_LOOKRIGHT);
		Enemies[0] = Monster;
		Monster.SetTile(42, 9);
		Enemies[1] = Monster;
		Monster.SetTile(78, 5);
		Enemies[2] = Monster;
	}
}

void cGame::InitEnemies2(int level) {
	if (level == 1) {
		//First Monster
		cEnemy2 Monster = cEnemy2();
		Monster.SetOrientation(false);
		Monster.SetWidthHeight(35, 35);
		Monster.SetMaxStep(22);
		Monster.SetTile(35, 7);
		int x, y;
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Monster.SetWidthHeight(35, 35);
		Monster.SetState(STATE_LOOKLEFT);
		Monster.SetShotDimensions(20, 26);
		Enemies2[0] = Monster;
	}
}

bool cGame::Loop()
{
	int playerX, playerY;
	Player.GetPosition(&playerX, &playerY);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (playerX<180) glOrtho(0+32, GAME_WIDTH+32, 0 + 16, GAME_HEIGHT + 16, 0, 1);
	else if (playerX>185 * 16) glOrtho(176* 16, 201 * 16, 0 + 16, GAME_HEIGHT + 16, 0, 1);
	else glOrtho(playerX-150,playerX +250, 0+16, GAME_HEIGHT+16, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res = true;
	//Process Input
	if (keys[27])	res = false;

	if (keys[GLUT_KEY_UP])			Player.Jump(Scene.GetCollisionMap());
	if (keys[GLUT_KEY_LEFT] && (!Player.IsOstioning()))			Player.MoveLeft(Scene.GetCollisionMap(), false);
	else if (keys[GLUT_KEY_RIGHT] && (!Player.IsOstioning()))	Player.MoveRight(Scene.GetCollisionMap(), false);
	else Player.Stop();

	if (keys[' ']) Player.Shot(Scene.GetMap(), (Player.GetState() == STATE_LOOKRIGHT || Player.GetState() == STATE_WALKRIGHT || Player.GetState() == STATE_JUMP_UP_RIGHT || Player.GetState() == STATE_FALLING_RIGHT));

	//Obtain the Rect of the shot to know if it collides with an enemy
	cRect playerShot;
	Player.GetShotArea(&playerShot);
	for (int i = 0; i < ENEMIES_1; ++i) {
		Enemies[i].Logic(Scene.GetCollisionMap(), &playerShot);
		cRect EnemyPos;
		Enemies[i].GetArea(&EnemyPos);
		if (Player.Collides(&EnemyPos)) Player.Ostion(Scene.GetCollisionMap());
	}
	for (int i = 0; i < ENEMIES_2; ++i) {
		Enemies2[i].Logic(Scene.GetCollisionMap(), &playerShot);
		cRect EnemyPos;
		cRect EnemyShotPos;
		Enemies2[i].GetArea(&EnemyPos);
		Enemies2[i].GetShotArea(&EnemyShotPos);
		if (Player.Collides(&EnemyPos) || Player.Collides(&EnemyShotPos)) Player.Ostion(Scene.GetCollisionMap());
	}

	Player.Logic(Scene.GetCollisionMap(), EnemiesPosition, ENEMIES_1, EnemiesPosition2, ENEMIES_2, EnemiesShot, ENEMIES_2);
	BurstMan.Logic(Scene.GetCollisionMap());
	return res;
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	glLoadIdentity();
	Scene.Draw(Data.GetID(IMG_BLOCKS));
	if (Player.IsShooting()) {
		if (Player.IsShootingRight()) Player.DrawShot(Data.GetID(IMG_SHOTRIGHT),true);
		else Player.DrawShot(Data.GetID(IMG_SHOTLEFT),false);
	}
	Player.Draw(Data.GetID(IMG_PLAYER));
	Player.DrawLiveBar(Data.GetID(IMG_GUI_MEGA));
	for (int i = 0; i < ENEMIES_1; ++i) {
		Enemies[i].Draw(Data.GetID(IMG_MONSTER));
	}
	BurstMan.Draw(Data.GetID(IMG_BOSS1));
	for (int i = 0; i < ENEMIES_2; ++i) {
		Enemies2[i].Draw(Data.GetID(IMG_PLAYER));
		if (Enemies2[i].IsShooting()) {
			Enemies2[i].DrawShot(Data.GetID(IMG_HELISHOT));
		}
	}
	if (BurstMan.IsShooting()) BurstMan.DrawShot(Data.GetID(IMG_HELISHOT));
	glutSwapBuffers();
 }
