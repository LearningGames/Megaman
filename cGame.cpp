#include "cGame.h"
#include "Globals.h"

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
	res = Data.LoadImage(IMG_BLOCKS,"tile01.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(level);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"megaman.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(35,35);
	Player.SetTile(4,3);
	Player.SetWidthHeight(35,35);
	Player.SetState(STATE_LOOKRIGHT);

	//Shot Initialization
	res = Data.LoadImage(IMG_SHOTRIGHT, "shootRight.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHOTLEFT, "shootLeft.png", GL_RGBA);
	if (!res) return false;
	Player.SetShotDimensions(20, 26);

	//Monster initialization
	res = Data.LoadImage(IMG_PLAYER, "megaman.png", GL_RGBA);
	if (!res) return false;
	InitEnemies(level);

	return res;
}

void cGame::InitEnemies(int level) {
	if (level == 1) {
		//First Monster
		cEnemy Monster = cEnemy();
		Monster.SetWidthHeight(35, 35);
		Monster.SetMaxStep(40);
		Monster.SetTile(16, 6);
		Monster.SetWidthHeight(35, 35);
		Monster.SetState(STATE_LOOKRIGHT);
		Enemies[0] = Monster;
		Monster.SetMaxStep(60);
		Monster.SetTile(42, 9);
		Enemies[1] = Monster;
		Monster.SetMaxStep(62);
		Monster.SetTile(78, 5);
		Enemies[2] = Monster;
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
	if (keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetCollisionMap());
	else if (keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetCollisionMap());
	else Player.Stop();

	if (keys[' ']) Player.Shot(Scene.GetMap(), (Player.GetState() == STATE_LOOKRIGHT || Player.GetState() == STATE_WALKRIGHT || Player.GetState() == STATE_JUMP_UP_RIGHT || Player.GetState() == STATE_FALLING_RIGHT));
	//Get if the shot collides some enemy
	int xShot, yShot;
	Player.GetShotPosition(&xShot, &yShot);
	//Monster.Move(Scene.GetMap());
	//Game Logic
	if (Player.IsHited(Enemies, ENEMIES_1)) Player.Stop();
	else Player.Logic(Scene.GetCollisionMap());
	for (int i = 0; i < ENEMIES_1; ++i) {
		Enemies[i].Move(Scene.GetMap(), xShot, yShot);
	}
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
	for (int i = 0; i < ENEMIES_1; ++i) {
		Enemies[i].Draw(Data.GetID(IMG_MONSTER));
	}

	glutSwapBuffers();
 }
