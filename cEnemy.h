#pragma once

#include "cTexture.h"
#include "Globals.h"
#include <stdio.h>
using namespace std;

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

class cEnemyRect
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
	void SetMaxStep(int max);
	void GetPosition(int *x, int *y);
	void SetTile(int tx, int ty);
	void GetTile(int *tx, int *ty);
	void SetWidthHeight(int w, int h);
	void GetWidthHeight(int *w, int *h);

	bool Collides(cEnemyRect *rc);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map);

	void GetArea(cEnemyRect *rc);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf);
	void DrawShotRect(int tex_id, float xo, float yo, float xf, float yf);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Jump(int *map);
	void Stop();
	void Logic(int *map);

	void Move(int *map, int xShot, int yShot);
	void Die();

	//Shooting functions
	bool IsHited(int xRival, int yRival);
	void Shot(int *map, bool isRight);
	bool IsShooting();
	bool IsShootingRight();
	void SetShotDimensions(int width, int height);
	void GetShotPosition(int *xResult, int *yResult);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();

	void Draw(int tex_id);

private:
	int x, y;
	int w, h;
	int state;
	int initialX;
	int maxStep;


	bool jumping;
	int jump_alfa;
	int jump_y;

	//shooting data
	bool shooting;			//Get if the bicho is shooting or not
	int xShot, yShot;		//Shot Position
	int wShot, hShot;		//Shot size
	int shotProgress;		//Shot Progres
	bool isRightShot;

	int seq, delay;
};
