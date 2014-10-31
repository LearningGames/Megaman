#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cBoss1.h"
#include "cData.h"
#include "cEnemy2.h"
#include "cEnemy.h"

#define GAME_WIDTH	400
#define GAME_HEIGHT 240
#define ENEMIES_1	3
#define ENEMIES_2	1

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	void InitEnemies(int level);
	void InitEnemies2(int level);
	void InitBoss(int level);
	bool Loop();
	void Finalize();

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	int level = 0;
	cScene Scene;
	cPlayer Player;
	cData Data;
	cEnemy Enemies[ENEMIES_1];
	cRect EnemiesPosition[ENEMIES_1];
	cRect EnemiesShot[ENEMIES_2];
	cRect EnemiesPosition2[ENEMIES_2];
	cEnemy2 Enemies2[ENEMIES_2];
	cBoss1 BurstMan;
};
