#pragma once

#include "cBicho.h"

#define PLAYER_START_CX		4
#define PLAYER_START_CY		1

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void DrawShot(int tex_id, bool isRight);
	void DrawLiveBar(int tex_id);
	void DrawLiveBar2(int tex_id,int num);
private:
	ISoundEngine* engine;
};
