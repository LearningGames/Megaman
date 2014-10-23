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

	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,GAME_WIDTH,0,GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_BLOCKS,"sheet.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"sprites.png",GL_RGBA);
	if(!res) return false;
	Player.SetWidthHeight(35,35);
	Player.SetTile(4,1);
	Player.SetWidthHeight(35,35);
	Player.SetState(STATE_LOOKRIGHT);

	//Shot Initialization
	res = Data.LoadImage(IMG_SHOTRIGHT, "shootRight.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHOTLEFT, "shootLeft.png", GL_RGBA);
	if (!res) return false;
	Player.SetShotDimensions(20, 26);

	//Monster initialization
	res = Data.LoadImage(IMG_PLAYER, "sprites.png", GL_RGBA);
	if (!res) return false;
	Monster.SetWidthHeight(35, 35);
	Monster.SetTile(5, 1);
	Monster.SetWidthHeight(35, 35);
	Monster.SetState(STATE_LOOKRIGHT);

	return res;
}

bool cGame::Loop()
{
	int playerX, playerY;
	Player.GetPosition(&playerX, &playerY);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(playerX-150,playerX +250, 0, GAME_HEIGHT, 0, 1);
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
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	if(keys[GLUT_KEY_UP])			Player.Jump(Scene.GetMap());
	if(keys[GLUT_KEY_LEFT])			Player.MoveLeft(Scene.GetMap());
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	else Player.Stop();

	if (keys[' ']) Player.Shot(Scene.GetMap(), (Player.GetState() == STATE_LOOKRIGHT || Player.GetState() == STATE_WALKRIGHT || Player.GetState() == STATE_JUMP_UP_RIGHT || Player.GetState() == STATE_FALLING_RIGHT));
	//Get if the shot collides some enemy
	int xShot, yShot;
	Player.GetShotPosition(&xShot, &yShot);
	if (Monster.IsHited(xShot, yShot)) Monster.Jump(Scene.GetMap());
	//Monster.Move(Scene.GetMap());
	//Game Logic
	Player.Logic(Scene.GetMap());
	Monster.Logic(Scene.GetMap());

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
	Monster.Draw(Data.GetID(IMG_MONSTER));

	glutSwapBuffers();
 }
