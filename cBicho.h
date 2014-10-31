#pragma once

#include "cTexture.h"
#include "Globals.h"
//#include "cEnemy.h"

#define FRAME_DELAY		3
#define STEP_LENGTH		3
#define JUMP_HEIGHT		60
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_WALKLEFT		1
#define STATE_JUMP_UP_LEFT	2
#define STATE_FALLING_LEFT	3
#define STATE_JUMP_HIT_LEFT 4
#define STATE_SHOOTLEFT		5
#define STATE_LOOKRIGHT		6
#define STATE_WALKRIGHT		7
#define STATE_JUMP_UP_RIGHT	8
#define STATE_FALLING_RIGHT	9
#define STATE_JUMP_HIT_RIGHT 10 
#define STATE_SHOOTRIGHT	11
#define STATE_HITED			12
#define STATE_DIE			13
#define STATE_TRANSFORM_RIGHT 14
#define STATE_MOVE_RIGHT 15

//Define type of Bicho
#define PLAYER			0
#define ENEMY1			1
#define	ENEMY2			2
#define BURSTMAN		3


//New defines
#define SHOT_STEP			5
#define DIST_SHOT			120
#define SHOT_OFFSET_X		42
#define SHOT_OFFSET_Y		20

#define SHOT_ENEMY_STEP			2
#define DIST_SHOT_ENEMY			80
#define SHOT_BOSS_STEP			3
#define DIST_SHOT_BOSS			150


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
	bool IsAlive();
	bool IsJumping();
	bool IsOstioning();
	void SetAlive(bool aliveState);
	void SetDeadTime(int time);
	int GetDeadTime();

	void ResetFrame();

	bool Collides(cRect *rc);
	bool CollideWithSomething(cRect EnemiesPosition[], int sizeEnemies1, cRect EnemiesPosition2[], int sizeEnemies2, cRect EnemiesShot[], int sizeShot);
	bool CollidesMapWall(int *map, bool right);
	bool CollidesMapFloor(int *map, bool nextStep);

	void GetArea(cRect *rc);
	void GetShotArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	void DrawShotRect(int tex_id, float xo, float yo, float xf, float yf);
	void DrawLiveBarRect(int tex_id, float xo, float yo, float xf, float yf);

	void MoveRight(int *map, bool boss);
	void MoveLeft(int *map, bool boss);
	void Jump(int *map);
	void Ostion(int *map);
	void Stop();
	void JumpLogic(int *map, bool boss);
	void FallingLogic(int *map);
	void Logic(int *map);

	//Shooting functions
	//bool IsHited(cEnemy Enemies[], int size);
	void Hited();
	void Shot(int *map, bool isRight);
	void ShotLogic(int type);
	bool IsShooting();
	bool IsShootingRight();
	void SetShotDimensions(int width, int height);
	void GetShotPosition(int *xResult, int *yResult);
	void SetShotPosition(int xResult, int yResult);
	void SetShotProgress(int prog);
	void EraseShot();
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

	bool isAlive;
	int deadTime;

	
	bool jumping;
	bool ostion;
	int jump_alfa;
	int jump_y;
	int jump_x;

	int xShot, yShot;		//Shot Position
	int wShot, hShot;		//Shot size
	int shotProgress;		//Shot Progres
	bool isRightShot;

	bool shooting;			//Get if the bicho is shooting or not
	int wLive, hLive;

	int seq,delay;
};
