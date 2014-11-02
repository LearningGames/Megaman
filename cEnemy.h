#pragma once

#include "cBicho.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		1
#define JUMP_HEIGHT		60
#define JUMP_STEP		4
#define MAX_STEP		60	

#define DEAD_TIME	30

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

	bool Logic(int *map, cRect *playerShot, int level);
	void Die();

	bool IsHited(int xRival, int yRival);

	void Draw(int tex_id);
};
