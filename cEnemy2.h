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
#define SHOT_STEP			3
#define DIST_SHOT			100

class cEnemy2 : public cBicho
{
public:
	cEnemy2(void);
	cEnemy2(int x, int y, int w, int h);
	~cEnemy2(void);

	void SetInitialPosition(int y);
	void SetOrientation(bool right);
	void SetMaxStep(int max);


	void Logic(int *map, int xShot, int yShot);

	void MoveDown(int *map);
	void MoveUp(int *map);
	void Die();

	//Shooting functions
	bool IsHited(int xRival, int yRival);

	void Draw(int tex_id);
	void DrawShot(int tex_id);

private:
	int initialY;
	int maxStep;
	bool alive;
	bool lookRight;
	int deadtime;

	bool startShoot;
	bool movingDown;

	int seq, delay;
};
