#include "cBoss1.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")
using namespace std;

cBoss1::cBoss1(void)
{
	start = false;
	first = true;
	shootingTime = 0;
	engine = createIrrKlangDevice();
}
cBoss1::~cBoss1(void){}

void cBoss1::Start(){
	start = true;
}

bool cBoss1::Logic(int *map, cRect *playerShot, int level)
{
	boolean result = false;
	if (IsAlive() && start) {
		if (first) {
			Jump(map, level);
			first = false;
		}
		else {
			if (Collides(playerShot)) {
				live++;
				if (live >= 4) {
					SetAlive(false);
					if (!IsLookingRight()) SetState(STATE_HITED);
					else SetState(STATE_HITED_LEFT);
					engine->play2D("shout.wav");
				}
				result = true;
			}
			if (IsShooting()) {
				ShotLogic(BURSTMAN,map);
			}
			if (IsJumping()) {
				if (GetState() >= STATE_LOOKLEFT && GetState() <= STATE_SHOOTLEFT) {
					MoveLeft(map, true, level);
				}
				else {
					MoveRight(map, true, level);
				}
				JumpLogic(map, true, level);
			}
			else if (!CollidesMapFloor(map, false, level)) {
				FallingLogic(map);
			}
			else {
				++shootingTime;
				if (shootingTime >= JUMP_TIME) {
					Jump(map, level);
					shootingTime = 0;
				}
				else if (shootingTime >= SHOT_TIME) {
					if (GetState() > STATE_LOOKLEFT && GetState() <= STATE_SHOOTLEFT) {
						SetState(STATE_LOOKLEFT);
					}
					else if (GetState() > STATE_LOOKRIGHT && GetState() < STATE_SHOOTRIGHT){
						SetState(STATE_LOOKRIGHT);
					}
				}
				else if (shootingTime >= 3) {
					if (GetState() >= STATE_LOOKLEFT && GetState() < STATE_SHOOTLEFT)
						SetState(STATE_SHOOTLEFT);
					else if (GetState() >= STATE_LOOKRIGHT && GetState() < STATE_SHOOTRIGHT)SetState(STATE_SHOOTRIGHT);
					if (shootingTime % 10 == 0)
						if (!IsShooting()) Shot(map, !(GetState() >= STATE_LOOKLEFT && GetState() <= STATE_SHOOTLEFT));
				}
				else if (shootingTime == 1)  {
					if (GetState() >= STATE_LOOKLEFT && GetState() <= STATE_SHOOTLEFT) {
						SetState(STATE_LOOKRIGHT);
					}
					else {
						SetState(STATE_LOOKLEFT);
					}
				}
			}
		}
	}
	return result;
}

//Draw functions
void cBoss1::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	float size = 1.0f / (490.0f/54.0f);
	float sizey = 1.0f / (490.0f / 72.0f);

	switch (GetState())
	{
	case STATE_SHOOTLEFT:
		xo = (3.0f*size)+(GetFrame()* size); yo =0.0f;
		NextFrame(3);
		break;
	case STATE_SHOOTRIGHT:
		xo = (3.0f*size) + (GetFrame()* size); yo = 1.0f*sizey;
		NextFrame(3);
		break;
	case STATE_LOOKLEFT:
		xo = (0.0f*size); yo = 0.0f;
		NextFrame(3);
		break;
	case STATE_LOOKRIGHT:
		xo = (0.0f*size); yo = 1.0f*sizey;
		NextFrame(3);
		break;
	case STATE_JUMP_UP_RIGHT:
		xo = 1.0f*size; yo = 1.0f*sizey;
		NextFrame(7);
		break;
	case STATE_JUMP_UP_LEFT:
		xo = 1.0f*size; yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_FALLING_RIGHT:
		xo = 2.0f*size; yo = 1.0f*sizey;
		NextFrame(7);
		break;
	case STATE_FALLING_LEFT:
		xo = 2.0f*size; yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_HITED:
		xo = (size * 6.0f); yo = 0.0f;
		break;
	case STATE_HITED_LEFT:
		xo = (size * 6.0f); yo = 1.0f*sizey;
		break;
	}
	xf = xo + size;
	yf = yo + sizey;

	DrawRect(tex_id, xo, yf, xf, yo);
}
void cBoss1::DrawShot(int tex_id)
{
	float xo, yo, xf, yf;
	xo = 0.0f + (GetFrame()*0.25f); yo = 1.0f;
	NextShotFrame(4);
	xf = xo + 0.25f;
	yf = yo - 0.5f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}

void cBoss1::NextShotFrame(int max)
{
	delayShot++;
	if (delayShot == FRAME_DELAY)
	{
		seqShot++;
		seqShot %= max;
		delayShot = 0;
	}
}

void cBoss1::DrawLiveBar(int tex_id){
	float xo, yo, xf, yf;
	xo = 0.0f;
	xf = 1.0f;
	yo = (live * 0.2f) + 0.2f;
	yf = (live * 0.2f);
	DrawLiveBarRect(tex_id, xo, yo, xf, yf);
}
