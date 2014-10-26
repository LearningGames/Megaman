#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "cMonster.h"
#include "cData.h"

#define GAME_WIDTH	400
#define GAME_HEIGHT 240

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
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
	cScene Scene;
	cPlayer Player;
	cMonster Monster;
	cData Data;
};
