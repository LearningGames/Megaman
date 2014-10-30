#include "cBoss1.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
using namespace std;

cBoss1::cBoss1(void)
{
}
cBoss1::~cBoss1(void){}

void cBoss1::Logic(int *map)
{
	Jump(map);
	if (IsShooting()) ShotLogic(false);
	if (IsJumping()) JumpLogic(map);
	else FallingLogic(map);
	//SetState(STATE_LOOKLEFT);
}

//Draw functions
void cBoss1::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	float size = 1.0f / (490.0f/54.0f);
	float sizey = 1.0f / (490.0f / 72.0f);

	switch (GetState())
	{
	case STATE_LOOKLEFT:
		xo = (3.0f*size)+(GetFrame()* size); yo =0.0f;
		NextFrame(3);
		break;
	case STATE_LOOKRIGHT:
		xo = 0.0f; yo = 0.0f*sizey;
		break;
	case STATE_JUMP_UP_RIGHT:
		xo = 0.0f; yo = 0.0f*sizey;
		NextFrame(7);
		break;
	case STATE_JUMP_UP_LEFT:
		xo = 1.0f*size; yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_FALLING_RIGHT:
		xo = 2.0f*size; yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_FALLING_LEFT:
		xo = 2.0f*size; yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_HITED:
		xo = (size * 7.0f) + (GetFrame()* size); yo = 5.0f*size;
		NextFrame(11);
		break;


	}
	xf = xo + size;
	yf = yo + sizey;

	DrawRect(tex_id, xo, yf, xf, yo);
}
void cBoss1::DrawShot(int tex_id, bool isRight)
{
	float xo, yo, xf, yf;
	xo = 0.0f + (GetFrame()*0.25f);
	NextFrame(4);
	xf = xo + 0.25f;
	yo = 1.0f;
	yf = 0.0f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}

