#pragma once

#include "cTexture.h"
#include "Globals.h"
//#include "cEnemy.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		3
#define JUMP_HEIGHT		60
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_JUMP_UP_LEFT	4
#define STATE_JUMP_UP_RIGHT	5
#define STATE_FALLING_LEFT	6
#define STATE_FALLING_RIGHT	7
#define STATE_HITED			8
#define STATE_JUMP_HIT_RIGHT 9 
#define STATE_JUMP_HIT_LEFT 10
#define STATE_DIE			11

//New defines
#define SHOT_STEP			5
#define DIST_SHOT			150
#define SHOT_OFFSET_X		42
#define SHOT_OFFSET_Y		20

#define SHOT_ENEMY_STEP			2
#define DIST_ENEMY_SHOT			80

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
	bool CollideWithSomething(cRect EnemiesPosition[], int sizeEnemies1, cRect EnemiesPosition2[], int sizeEnemies2, cRect EnemiesShot[], int sizeShot);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map, bool nextStep);

	void GetArea(cRect *rc);
	void GetShotArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	void DrawShotRect(int tex_id, float xo, float yo, float xf, float yf);
	void DrawLiveBarRect(int tex_id, float xo, float yo, float xf, float yf);

	void MoveRight(int *map);
	void MoveLeft(int *map);
	void Jump(int *map);
	void Ostion(int *map);
	void Stop();
	void JumpLogic(int *map);
	void Logic(int *map, cRect EnemiesPosition[], int sizeEnemies1, cRect EnemiesPosition2[], int sizeEnemies2, cRect EnemiesShot[], int sizeShot);

	//Shooting functions
	//bool IsHited(cEnemy Enemies[], int size);
	void Hited();
	void Shot(int *map, bool isRight);
	void ShotLogic(bool enemy);
	bool IsShooting();
	bool IsShootingRight();
	void SetShotDimensions(int width, int height);
	void GetShotPosition(int *xResult, int *yResult);
	void SetShotPosition(int xResult, int yResult);
	void SetLiveBar(int width, int height);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	int live;
	bool ShotCollidesWall(int *map);
	
private:
	int x,y;
	int w,h;
	int state;

	
	bool jumping;
	bool ostion;
	int jump_alfa;
	int jump_y;


	//shooting data
	bool shooting;			//Get if the bicho is shooting or not
	int xShot, yShot;		//Shot Position
	int wShot, hShot;		//Shot size
	int shotProgress;		//Shot Progres
	int wLive, hLive;
	bool isRightShot;

	int seq,delay;
};
