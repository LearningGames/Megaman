#pragma once

#include "cBicho.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		1
#define JUMP_HEIGHT		60
#define JUMP_STEP		4
#define MAX_STEP		60	

//New defines
#define SHOT_STEP			3
#define DIST_SHOT			100

#define DEAD_TIME	30

class cEnemy2 : public cBicho
{
public:
	cEnemy2(void);
	cEnemy2(int x, int y, int w, int h);
	~cEnemy2(void);

	void SetInitialPosition(int y);
	void SetMaxStep(int max);
	void NextShotFrame(int max);

	bool Logic(int *map, cRect *playerShot, int level);

	void MoveDown(int *map);
	void MoveUp(int *map);
	void Die();

	void Draw(int tex_id);
	void DrawShot(int tex_id);

private:
	int initialY;
	int maxStep;

	bool lookRight;
	bool movingDown;
	int seqShot, delayShot;
};
