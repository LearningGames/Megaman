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
};
