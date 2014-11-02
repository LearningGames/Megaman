#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "cBicho.h"
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")

#define FRAME_DELAY		3
#define STEP_LENGTH		3
#define JUMP_HEIGHT		60
#define JUMP_STEP		4

//New defines
#define SHOT_STEP			5
#define DIST_SHOT			150

#define SHOT_TIME		120
#define JUMP_TIME		160

class cBoss2 : public cBicho
{
public:
	cBoss2(void);
	cBoss2(int x, int y, int w, int h);
	~cBoss2(void);

	bool Logic(int *map, cRect *playerShot, int level);
	void Start();
	void Draw(int tex_id);
	void DrawShot(int tex_id);

	void NextShotFrame(int max);
	void DrawLiveBar(int tex_id);

private:
	bool start;
	bool first;
	int shootingTime;
	int stop_time;
	int seqShot, delayShot;
	ISoundEngine* engine;
};
