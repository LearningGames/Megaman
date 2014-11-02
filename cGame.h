#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cBoss1.h"
#include "cBoss2.h"
#include "cData.h"
#include "cEnemy2.h"
#include "cEnemy.h"

#define GAME_WIDTH	400
#define GAME_HEIGHT 240
#define ENEMIES_11	5
#define ENEMIES_21	4
#define ENEMIES_12	3
#define ENEMIES_22	4

#define SCREEN_MENU			0
#define SCREEN_CREDITS		1
#define SCREEN_INSTRUCTIONS	2
#define SCREEN_GAME			3
#define SCREEN_TWO_PLAYERS  4
#define SCREEN_INSTRUCTIONS2 5

#define DEAD_TIME	60

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	void InitEnemies(int level);
	void InitEnemies2(int level);
	void InitBoss(int level);
	void InitPlayer2();
	bool Loop();
	void Finalize();
	void Reset(int level);
	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	void LogicLevel1();
	void LogicLevel2();
	void LogicVersusMode();
	//Output
	void Render();
	void drawImage(int i);

private:
	unsigned char keys[256];
	int level = 0;
	int state;
	int deadtime;
	int deadBosstime;
	cScene Scene;
	cPlayer Player;
	cPlayer Player2;
	cData Data;
	cEnemy EnemiesLevel1[ENEMIES_11];
	cEnemy2 Enemies2Level1[ENEMIES_21];
	cEnemy EnemiesLevel2[ENEMIES_12];
	cEnemy2 Enemies2Level2[ENEMIES_22];
	cBoss1 BurstMan;
	cBoss2 RoundMan;
	ISoundEngine* engine;
	bool gaming;
};
