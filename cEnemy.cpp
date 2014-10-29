#include "cEnemy.h"
#include "cScene.h"
#include "Globals.h"

cEnemy::cEnemy(void)
{
	seq = 0;
	delay = 0;
	alive = true;
	deadtime = 0;
}
cEnemy::~cEnemy(void){}

void cEnemy::Logic(int *map, cRect *playerShot, cPlayer player)
{
	if (alive && GetState() != STATE_DIE) {
		cRect playerArea;
		player.GetArea(&playerArea);
		if (Collides(&playerArea)) {
			OutputDebugString("Collision Player \n");
			player.Jump(map);
		}
		if (Collides(playerShot)) {
			Die();
		}
		/*else if (!CollidesMapFloor(map,true)) {
			if (GetState() == STATE_WALKLEFT) MoveRight(map);
			else if (GetState() == STATE_WALKRIGHT) MoveLeft(map);
		}
		else if (GetState() == STATE_WALKLEFT) MoveLeft(map);
		else if (GetState() == STATE_WALKRIGHT) MoveRight(map);
		else MoveRight(map);*/
	}
	else if (alive) {
		deadtime++;
		if (deadtime > 30) alive = false;
	}
}

void cEnemy::Die() {
	SetState(STATE_DIE);
}
void cEnemy::MoveLeft(int *map)
{
	int xEnemy, yEnemy;
	GetPosition(&xEnemy, &yEnemy);
	SetPosition(xEnemy - STEP_LENGTH, yEnemy);
	if (GetState() != STATE_WALKLEFT)
		{
			SetState(STATE_WALKLEFT);
			seq = 0;
			delay = 0;
		}
}
void cEnemy::MoveRight(int *map)
{
	int xEnemy, yEnemy;
	GetPosition(&xEnemy, &yEnemy);
	SetPosition(xEnemy + STEP_LENGTH, yEnemy);
		if (GetState() != STATE_WALKRIGHT)
		{
			SetState(STATE_WALKRIGHT);
			seq = 0;
			delay = 0;
		}
}
void cEnemy::Stop()
{
	switch (GetState())
		{
		case STATE_WALKLEFT:	SetState(STATE_LOOKLEFT);		break;
		case STATE_WALKRIGHT:	SetState(STATE_LOOKRIGHT);	break;
		case STATE_FALLING_LEFT:SetState(STATE_LOOKLEFT);		break;
		case STATE_FALLING_RIGHT:SetState(STATE_LOOKRIGHT);	break;
		case STATE_JUMP_UP_LEFT:SetState(STATE_LOOKLEFT);		break;
		case STATE_JUMP_UP_RIGHT:SetState(STATE_LOOKRIGHT);	break;
		}
}

bool cEnemy::IsHited(int xRival, int yRival){
	//35 = w&h && xR+10 = wShot/2 && xY+13 = hShot/2
	int xEnemy, yEnemy;
	GetPosition(&xEnemy, &yEnemy);
	if (xEnemy + 35 >= xRival - (10) && xEnemy + 35 <= xRival + (10)) {
		if (((yEnemy + 35 / 2) >= (yRival - 13)) && ((yEnemy + 35 / 2) <= (yRival + 13))) return true;
		else return false;
	}
	else return false;
}

void cEnemy::Draw(int tex_id)
{
	if (alive) {
		float xo, yo, xf, yf;
		float size = 1.0f / 14.0f;
	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:
		xo = 1.0f * size;	yo = 2.0f*size;
		break;
		//4
	case STATE_LOOKRIGHT:
		xo = 12.0f * size; yo = 2.0f*size;
		break;
		//1..3
	case STATE_WALKLEFT:
		xo = (6.0f * size) - (GetFrame()* size);	yo = 2.0f*size;
		NextFrame(6);
		break;
		//4..6
	case STATE_WALKRIGHT:
		xo = (size * 7) + (GetFrame()* size); yo = 2.0f*size;
		NextFrame(6);
		break;
	case STATE_JUMP_UP_RIGHT:
		xo = (size * 8.0f); yo = 2.0f*size;
		NextFrame(4);
		break;
	case STATE_JUMP_UP_LEFT:
		xo = (size * 5.0f); yo = 2.0f*size;
		NextFrame(7);
		break;
	case STATE_FALLING_RIGHT:
		xo = (size * 7.0f); yo = 2.0f*size;
		NextFrame(7);
		break;
	case STATE_FALLING_LEFT:
		xo = (size * 6.0f); yo = 2.0f*size;
		NextFrame(7);
		break;
		//8
	case STATE_DIE:
		xo = (size * 6) - (GetFrame()* size);	yo = 4.0f*size;
		NextFrame(7);
		break;
		}
		xf = xo + size;
		yf = yo + size;

		DrawRect(tex_id, xo, yf, xf, yo);
	}
}
