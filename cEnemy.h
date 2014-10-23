#pragma once

#include "cTexture.h"
#include "Globals.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		3
#define JUMP_HEIGHT		80
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_JUMP_UP_LEFT	4
#define STATE_JUMP_UP_RIGHT	5
#define STATE_FALLING_LEFT	6
#define STATE_FALLING_RIGHT	7

class cRectEnemy
{
public:
	int left, top,
		right, bottom;
};

class cEnemy
{
public:
	cEnemy(void);
	cEnemy(int x, int y, int w, int h);
	~cEnemy(void);

	void SetPosition(int x, int y);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);

	bool Collides(cRectEnemy *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);
	void GetArea(cRectEnemy *rc);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Move(int *map);
	void Jump(int *map);
	void Stop();
	void Logic(int *map);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

private:
	int x, y;
	int w, h;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq, delay;
};
