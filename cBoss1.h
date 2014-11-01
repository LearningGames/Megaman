#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cBicho.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		3
#define JUMP_HEIGHT		60
#define JUMP_STEP		4

//New defines
#define SHOT_STEP			5
#define DIST_SHOT			150

#define SHOT_TIME		120
#define JUMP_TIME		160


class cBoss1 : public cBicho
{
public:
	cBoss1(void);
	cBoss1(int x, int y, int w, int h);
	~cBoss1(void);

	bool Logic(int *map, cRect *playerShot);

	void Draw(int tex_id);
	void DrawShot(int tex_id);

	void NextShotFrame(int max);
	void DrawLiveBar(int tex_id);

private:
	bool first;
	int shootingTime;

	int seqShot, delayShot;
};
