#include "cBoss2.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
#include <irrKlang.h>
using namespace irrklang;
#pragma comment(lib, "irrKlang.lib")
using namespace std;

cBoss2::cBoss2(void)
{
	first = true;
	shootingTime = 0;
	stop_time = 0;
	engine = createIrrKlangDevice();
}
cBoss2::~cBoss2(void){}

void cBoss2::Start() {
	start = true;
}

bool cBoss2::Logic(int *map, cRect *playerShot, int level)
{
	boolean result = false;
	if (start) {
		if (IsAlive()) {
			if (first) {
				Jump(map, level);
				first = false;
			}
			if (IsJumping()) JumpLogic(map, false, level);
			else if (CollidesMapFloor(map, false, level) && CollidesMapWall(map, IsLookingRight(),level)) {
				if (IsLookingRight()) {
					MoveLeft(map, true, level);
				}
				else MoveRight(map, true, level);
				Jump(map, level);
			}
			else if (Collides(playerShot)){
				live++;
				if (live >= 4){
					engine->play2D("bossdead.wav");
					SetAlive(false);
					if (!IsLookingRight())SetState(STATE_HITED);
					else SetState(STATE_HITED_LEFT);
				}
				result = true;
			}
			else if (CollidesMapFloor(map, false, level)) {
				if (IsLookingRight()) MoveRight(map, true, level);
				else MoveLeft(map, true, level);
			}
			else FallingLogic(map);
		}
	}
	return result;
}

//Draw functions
void cBoss2::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	float size = 1.0f / 5.0f;
	float sizey = 1.0f / 5.0f;
	float aux;

	switch (GetState())
	{
	case STATE_LOOKLEFT:
		xo = (0.0f*size); yo = 0.0f;
		break;
	case STATE_LOOKRIGHT:
		xo = (5.0f*size); yo = 2.0f*sizey;
		NextFrame(3);
		break;
		case STATE_JUMP_UP_LEFT:
		xo = (1.0f*size);  yo = 0.0f;
			//NextFrame(4);
		break;
		case STATE_JUMP_UP_RIGHT:
			xo = (3.0f*size);  yo = 2.0f*sizey;
			//NextFrame(4);
			break;
		case STATE_WALKLEFT:
		xo = (3.0f*size) - (GetFrame()* size); yo = 1.0f*sizey;
		NextFrame(4);
		break;
		case STATE_WALKRIGHT:
			xo = (1.0f*size) + (GetFrame()* size); yo = 3.0f*sizey;
			NextFrame(4);
			break;
	case STATE_FALLING_LEFT:
		aux = ((GetFrame()* size) / 3);
		if ((int)aux % 1 == 0) {
			xo = (2.0f*size) + ((GetFrame() / 3)* size);  yo = 0.0f;
		}
		NextFrame(9);
		break;
	case STATE_FALLING_RIGHT:
		aux = ((GetFrame()* size) / 3);
		if ((int)aux % 1 == 0) {
			xo = (2.0f*size) - ((GetFrame() / 3)* size);  yo = 2.0f*sizey;
		}
		NextFrame(9);
		break;
	case STATE_HITED:
		xo = (size * 1.0f); yo = 0.0f;
		break;
	case STATE_HITED_LEFT:
		xo = (size * 3.0f); yo = 2.0f*sizey;
		break;
	default:
		xo = 0.0f; yo = 0.0f*sizey;
		break;
	}
	xf = xo + size;
	yf = yo + sizey;

	DrawRect(tex_id, xo, yf, xf, yo);
}
void cBoss2::DrawShot(int tex_id)
{
	float xo, yo, xf, yf;
	xo = 1.0f - (seqShot*(1.0f / 7.0f));
	NextShotFrame(7);
	xf = xo - (1.0f / 7.0f);
	yo = 1.0f;
	yf = 0.0f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}

void cBoss2::NextShotFrame(int max)
{
	delayShot++;
	if (delayShot == FRAME_DELAY)
	{
		seqShot++;
		seqShot %= max;
		delayShot = 0;
	}

}
void cBoss2::DrawLiveBar(int tex_id){
		float xo, yo, xf, yf;
		xo = 0.0f;
		xf = 1.0f;
		yo = (live * 0.2f) + 0.2f;
		yf = (live * 0.2f);
		DrawLiveBarRect(tex_id, xo, yo, xf, yf);
	}

