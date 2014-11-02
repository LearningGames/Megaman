#include "cGame.h"
#include "Globals.h";
#include <iostream>;
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")


cGame::cGame(void)
{
	state = SCREEN_MENU;
	engine = createIrrKlangDevice();
	gaming = false;
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

	res = Data.LoadImage(IMG_MENU, "menu.png", GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_INST, "instructions.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_CREDITS, "credits.png", GL_RGBA);
	if (!res) return false;

	res = Data.LoadImage(IMG_LEVEL1,"tile01.png",GL_RGBA);
	if(!res) return false;
	res = Data.LoadImage(IMG_LEVEL2, "tile02.png", GL_RGBA);
	if (!res) return false;
	level = Scene.GetCurrentLevel();
	res = Scene.LoadLevel(level,1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"megaman.png",GL_RGBA);
	if(!res) return false;

	//Shot Initialization
	res = Data.LoadImage(IMG_SHOTRIGHT, "shootRight.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_SHOTLEFT, "shootLeft.png", GL_RGBA);
	if (!res) return false;

	//Barra vida initialization
	res = Data.LoadImage(IMG_GUI_MEGA, "guimega.png", GL_RGBA);
	Player.SetLiveBar(80, 16);
	res = Data.LoadImage(IMG_GUI_ROUND, "vidaRound.png", GL_RGBA);
	Player.SetLiveBar(80, 16);
	res = Data.LoadImage(IMG_GUI_BURST, "vidaBurst.png", GL_RGBA);
	Player.SetLiveBar(80, 16);
	Player.isPlayer = true;

	//Monster initialization
	res = Data.LoadImage(IMG_MONSTER, "megaman.png", GL_RGBA);
	if (!res) return false;
	res = Data.LoadImage(IMG_HELISHOT, "helishot.png", GL_RGBA);
	if (!res) return false;
	
	res = Data.LoadImage(IMG_BOSS1, "boss1.png", GL_RGBA);
	res = Data.LoadImage(IMG_BOSS1SHOT, "bubble.png", GL_RGBA);
	res = Data.LoadImage(IMG_BOSS2, "boss2.png", GL_RGBA);
	res = Data.LoadImage(IMG_INST2, "instructions2.png", GL_RGBA);

	//Init Player
	Player.SetWidthHeight(35, 35);
	Player.SetTile(3, 4);
	Player.SetWidthHeight(35, 35);
	Player.SetState(STATE_LOOKRIGHT);
	Player.SetShotDimensions(20, 26);
	Player.SetLiveBar(80, 16);

	InitEnemies2(level);
	InitEnemies(level);
	InitBoss(level);
	return res;
}

void cGame::Reset(int level)
{
	//Init Player
	Player.Reset(3,4);
	InitEnemies2(level);
	InitEnemies(level);
	InitBoss(level);
}

void cGame::InitBoss(int level) {
	switch (level) {
	case 1: 
		BurstMan.SetWidthHeight(54, 72);
		BurstMan.SetTile(194, 4);
		BurstMan.SetWidthHeight(54, 72);
		BurstMan.SetState(STATE_LOOKLEFT);
		BurstMan.SetShotDimensions(20, 26);
		BurstMan.isBoss = true;
		break;
	case 2:
		RoundMan.SetWidthHeight(57, 57);
		RoundMan.SetTile(194, 1);
		RoundMan.SetWidthHeight(57, 57);
		RoundMan.SetState(STATE_LOOKLEFT);
		RoundMan.isBoss = true;
	}	
}


void cGame::InitEnemies(int level) {
	cEnemy Monster = cEnemy();
	switch (level) {
	case 1:
		//First Monster
		Monster.SetWidthHeight(35, 35);
		Monster.SetTile(16, 6);
		Monster.SetState(STATE_LOOKRIGHT);
		EnemiesLevel1[0] = Monster;
		Monster.SetTile(42, 9);
		EnemiesLevel1[1] = Monster;
		Monster.SetTile(78, 5);
		EnemiesLevel1[2] = Monster;
		Monster.SetPosition(866, 48);
		EnemiesLevel1[3] = Monster;
		Monster.SetPosition(1690, 48);
		EnemiesLevel1[4] = Monster;
		break;
	case 2:
		//First Monster
		cEnemy Monster = cEnemy();
		Monster.SetWidthHeight(35, 35);
		Monster.SetPosition(219, 48);
		Monster.SetState(STATE_LOOKRIGHT);
		EnemiesLevel2[0] = Monster;
		Monster.SetPosition(828, 128);
		EnemiesLevel2[1] = Monster;
		Monster.SetPosition(1641, 32);
		EnemiesLevel2[2] = Monster;
		break;
	}
}

void cGame::InitEnemies2(int level) {
	cEnemy2 Monster = cEnemy2();
	Monster.SetWidthHeight(35, 35);
	Monster.SetState(STATE_LOOKLEFT);
	Monster.SetShotDimensions(20, 26);
	int x, y;
	switch (level) {
	case 1:
		//First Monster
		Monster.SetMaxStep(22);
		Monster.SetTile(35, 7);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level1[0] = Monster;
		Monster.SetMaxStep(22);
		Monster.SetPosition(1110, 65);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level1[1] = Monster;
		Monster.SetMaxStep(22);
		Monster.SetPosition(1448, 150);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level1[2] = Monster;
		Monster.SetMaxStep(30);
		Monster.SetPosition(2290, 150);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level1[3] = Monster;
		break;
	case 2:
		//First Monster
		Monster.SetMaxStep(22);
		Monster.SetPosition(0,0);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level2[0] = Monster;
		Monster.SetMaxStep(22);
		Monster.SetPosition(1074, 120);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level2[1] = Monster;
		Monster.SetMaxStep(22);
		Monster.SetPosition(2007, 120);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level2[2] = Monster;
		Monster.SetMaxStep(25);
		Monster.SetPosition(2415, 100);
		Monster.GetPosition(&x, &y);
		Monster.SetInitialPosition(y);
		Enemies2Level2[3] = Monster;
		break;
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
	if (state != SCREEN_GAME) {
		engine->removeSoundSource("music1.wav");
		engine->removeSoundSource("music2.wav");
		gaming = false;
	}

	if (state == SCREEN_MENU){ //START SCREEN_MENU
		if (keys['1']){
			state = SCREEN_GAME;
		}
		if (keys['2']){
			state = SCREEN_INSTRUCTIONS;
		}
		if (keys['3']){
			state = SCREEN_CREDITS;
		}
		if (keys['4']){
			state = SCREEN_TWO_PLAYERS;
		}
		if (keys['E'] || keys['e']){
			res = false;
		}
	}//END SCREEN_MENU

	else if (state == SCREEN_CREDITS){
		if (keys['5']){
			state = SCREEN_MENU;
		}
	}

	else if (state == SCREEN_INSTRUCTIONS){
		if (keys['5']){
			state = SCREEN_MENU;
		}
		else if (keys['8']){
			state = SCREEN_INSTRUCTIONS2;
		}
	}
	else if (state == SCREEN_INSTRUCTIONS2){
		if (keys['5']){
			state = SCREEN_MENU;
		}
		else if (keys['9']){
			state = SCREEN_INSTRUCTIONS;
		}
	}

	else if (state == SCREEN_GAME){ //START SCREEN_MENU
		if (!gaming){
			if(Scene.GetCurrentLevel()==1)engine->play2D("music1.wav", true);
			else engine->play2D("music2.wav");
			gaming = true;
			Reset (Scene.GetCurrentLevel() );
		}
		if (keys[27]){
			state = SCREEN_MENU;
			engine->stopAllSounds();
		}
		if (keys[GLUT_KEY_UP])			Player.Jump(Scene.GetCollisionMap());
		if (keys[GLUT_KEY_LEFT] && (!Player.IsOstioning()))			Player.MoveLeft(Scene.GetCollisionMap(), false);
		else if (keys[GLUT_KEY_RIGHT] && (!Player.IsOstioning()))	Player.MoveRight(Scene.GetCollisionMap(), false);
		else Player.Stop();

		if (keys[' ']){
			Player.Shot(Scene.GetMap(), (Player.GetState() == STATE_LOOKRIGHT || Player.GetState() == STATE_WALKRIGHT || Player.GetState() == STATE_JUMP_UP_RIGHT || Player.GetState() == STATE_FALLING_RIGHT));
		}

		if (keys['a']) {
			
			engine->removeSoundSource("music1.wav");
			Scene.NextLevel();

			engine->play2D("music2.wav", true);
		//engine->removeAllSoundSources();
			Init();
		}
		if (keys['b']) {
			Player.SetPosition(2700, 16);
		}
		if (!Player.IsAlive()){
			++deadtime;
			if (deadtime >= DEAD_TIME) {
				deadtime = 0;
				Reset(Scene.GetCurrentLevel());
			}
		}
		else {
			//Obtain the Rect of the shot to know if it collides with an enemy
			cRect playerShot;
			Player.GetShotArea(&playerShot);
			cRect EnemyPos;
			cRect EnemyShotPos;
			if (level == 1) {
				if (BurstMan.IsAlive()) {
					for (int i = 0; i < ENEMIES_11; ++i) {
						if (EnemiesLevel1[i].Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();;
						EnemiesLevel1[i].GetArea(&EnemyPos);
						if (EnemiesLevel1[i].IsAlive() && Player.Collides(&EnemyPos)) Player.Ostion(Scene.GetCollisionMap());
					}
					for (int i = 0; i < ENEMIES_21; ++i) {
						if (Enemies2Level1[i].Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();;
						Enemies2Level1[i].GetArea(&EnemyPos);
						Enemies2Level1[i].GetShotArea(&EnemyShotPos);
						if (Player.Collides(&EnemyShotPos)) Enemies2Level1[i].EraseShot();
						if (Enemies2Level1[i].IsAlive() && (Player.Collides(&EnemyPos) || Player.Collides(&EnemyShotPos))) Player.Ostion(Scene.GetCollisionMap());
					}
					//Boss Area
					BurstMan.GetArea(&EnemyPos);
					BurstMan.GetShotArea(&EnemyShotPos);
					if (Player.Collides(&EnemyShotPos)) BurstMan.EraseShot();
					if (BurstMan.IsAlive() && (Player.Collides(&EnemyPos) || Player.Collides(&EnemyShotPos))) Player.Ostion(Scene.GetCollisionMap());
					int x, y;
					Player.GetPosition(&x, &y);
					if (x >= 2855 && x <= 3000 && y <= 80) {
						BurstMan.Start();
					}
					if (BurstMan.Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();
				}
				else if (deadBosstime >= DEAD_TIME) {
					deadBosstime = 0;
					engine->removeSoundSource("music1.wav");
					Scene.NextLevel();

					engine->play2D("music2.wav", true);
					//engine->removeAllSoundSources();
					Init();
				}
				else ++deadBosstime;
			}
			else if (level == 2) {
				int x, y;
				Player.GetPosition(&x, &y);
				if (x >= 2855 && x <= 3000 && y <= 20) {
					RoundMan.Start();
				}
				if (RoundMan.IsAlive()) {
					for (int i = 0; i < ENEMIES_21; ++i) {
						if (EnemiesLevel2[i].Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();;
						EnemiesLevel2[i].GetArea(&EnemyPos);
						if (EnemiesLevel2[i].IsAlive() && Player.Collides(&EnemyPos)) Player.Ostion(Scene.GetCollisionMap());
					}
					for (int i = 1; i < ENEMIES_22; ++i) {
						if (Enemies2Level2[i].Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();;
						Enemies2Level2[i].GetArea(&EnemyPos);
						Enemies2Level2[i].GetShotArea(&EnemyShotPos);
						if (Player.Collides(&EnemyShotPos)) Enemies2Level2[i].EraseShot();
						if (Enemies2Level2[i].IsAlive() && (Player.Collides(&EnemyPos) || Player.Collides(&EnemyShotPos))) Player.Ostion(Scene.GetCollisionMap());
					}
					RoundMan.GetArea(&EnemyPos);
					if (RoundMan.IsAlive() && Player.Collides(&EnemyPos)) Player.Ostion(Scene.GetCollisionMap());
					if (RoundMan.Logic(Scene.GetCollisionMap(), &playerShot) && (Player.IsShooting())) Player.EraseShot();

				}
				else if (deadBosstime >= DEAD_TIME) {
					deadBosstime = 0;
					engine->removeSoundSource("music1.wav");
					state = SCREEN_MENU;
					engine->stopAllSounds();
				}
				else ++deadBosstime;
			}

			Player.Logic(Scene.GetCollisionMap());
		}
	}//END SCREEN_GAME
	int x, y;
	Player.GetPosition(&x, &y);
	char s[256];
	sprintf(s, "x: %d, y: %d \n", x, y);
	OutputDebugString(s);
	return res;
}

void cGame::drawImage(int i){
	glEnable(GL_TEXTURE_2D);
	
	if(i==1) glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_MENU));
	else if (i == 2) glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_INST));
	else if (i == 3)glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_CREDITS));
	else if (i == 4)glBindTexture(GL_TEXTURE_2D, Data.GetID(IMG_INST2));

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1, 0);
	glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1, 1);
	glVertex2f(1.0f, -1.0f);
	glTexCoord2f(0, 1);
	glVertex2f(-1.0f, -1.0f);
	glEnd();
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glDisable(GL_TEXTURE_2D);
}

//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	if (state == SCREEN_GAME){
		if (Scene.GetCurrentLevel() == 1) Scene.Draw(Data.GetID(IMG_LEVEL1));
		else Scene.Draw(Data.GetID(IMG_LEVEL2));
		if (Player.IsShooting()) {
			if (Player.IsShootingRight()) Player.DrawShot(Data.GetID(IMG_SHOTRIGHT), true);
			else Player.DrawShot(Data.GetID(IMG_SHOTLEFT), false);
		}
		Player.Draw(Data.GetID(IMG_PLAYER));
		if (level == 1) {
			for (int i = 0; i < ENEMIES_11; ++i) {
				EnemiesLevel1[i].Draw(Data.GetID(IMG_MONSTER));
			}

			for (int i = 0; i < ENEMIES_21; ++i) {
				Enemies2Level1[i].Draw(Data.GetID(IMG_PLAYER));
				if (Enemies2Level1[i].IsShooting() && Enemies2Level1[i].IsAlive()) {
					Enemies2Level1[i].DrawShot(Data.GetID(IMG_HELISHOT));
				}
			}
			BurstMan.Draw(Data.GetID(IMG_BOSS1));
			if (BurstMan.IsShooting() && BurstMan.IsAlive()) BurstMan.DrawShot(Data.GetID(IMG_BOSS1SHOT));
		}
		else if (level == 2) {
			for (int i = 0; i < ENEMIES_12; ++i) {
				EnemiesLevel2[i].Draw(Data.GetID(IMG_MONSTER));
			}

			for (int i = 1; i < ENEMIES_22; ++i) {
				Enemies2Level2[i].Draw(Data.GetID(IMG_PLAYER));
				if (Enemies2Level2[i].IsShooting() && Enemies2Level2[i].IsAlive()) {
					Enemies2Level2[i].DrawShot(Data.GetID(IMG_HELISHOT));
				}
			}
			RoundMan.Draw(Data.GetID(IMG_BOSS2));
		}
		if(level == 2)RoundMan.DrawLiveBar(Data.GetID(IMG_GUI_ROUND));
		if(level == 1)BurstMan.DrawLiveBar(Data.GetID(IMG_GUI_BURST));
		Player.DrawLiveBar(Data.GetID(IMG_GUI_MEGA));
	}
	else{
		char imatge[256];
		switch (state){
			case SCREEN_MENU:
				sprintf(imatge, "menu.png");
				drawImage(1);
			break;
			case SCREEN_CREDITS:
				sprintf(imatge, "credits.png");
				drawImage(3);
				break;
			case SCREEN_INSTRUCTIONS:
				sprintf(imatge, "instructions.png");
				drawImage(2);
				break;
			case SCREEN_INSTRUCTIONS2:
				sprintf(imatge, "instructions2.png");
				drawImage(4);
				break;
		}
		OutputDebugString(imatge);
	}
	glLoadIdentity();
	glutSwapBuffers();
 }
