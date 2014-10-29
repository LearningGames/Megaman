#pragma once

#include "cBicho.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		1
#define JUMP_HEIGHT		60
#define JUMP_STEP		4
#define MAX_STEP		60

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_JUMP_UP_LEFT	4
#define STATE_JUMP_UP_RIGHT	5
#define STATE_FALLING_LEFT	6
#define STATE_FALLING_RIGHT	7

#define STATE_DIE			8	

//New defines
#define SHOT_STEP			5
#define DIST_SHOT			150

class cEnemy : public cBicho
{
public:
	cEnemy(void);
	cEnemy(int x, int y, int w, int h);
	~cEnemy(void);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Stop();
	/*void Logic(int *map);*/

	void Logic(int *map, int xShot, int yShot);
	void Die();

	bool IsHited(int xRival, int yRival);

	void Draw(int tex_id);

private:
	bool alive;
	int deadtime;

	int seq, delay;
};
