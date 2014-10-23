#include "cMonster.h"

cMonster::cMonster() {}
cMonster::~cMonster(){}

void cMonster::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	float size = 1.0f / 14.0f;


	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:
		xo = 6.0f * size;	yo = 0.0f;
		break;
		//4
	case STATE_LOOKRIGHT:
		xo = 7.0f * size; yo = 0.0f;
		break;
		//1..3
	case STATE_WALKLEFT:
		xo = (6.0f * size) - (GetFrame()* size);	yo = 0.0f;
		NextFrame(7);
		break;
		//4..6
	case STATE_WALKRIGHT:
		xo = (size * 7) + (GetFrame()* size); yo = 0.0f;
		NextFrame(7);
		break;
	case STATE_JUMP_UP_RIGHT:
		xo = (size * 8.0f); yo = size;
		NextFrame(7);
		break;
	case STATE_JUMP_UP_LEFT:
		xo = (size * 5.0f); yo = size;
		NextFrame(7);
		break;
	case STATE_FALLING_RIGHT:
		xo = (size * 7.0f); yo = size;
		NextFrame(7);
		break;
	case STATE_FALLING_LEFT:
		xo = (size * 6.0f); yo = size;
		NextFrame(7);
		break;


	}
	xf = xo + size;
	yf = yo + size;

	DrawRect(tex_id, xo, yf, xf, yo);
}