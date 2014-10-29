#include "cEnemy2.h"
#include "cScene.h"
#include "Globals.h"

cEnemy2::cEnemy2(void)
{
	seq = 0;
	delay = 0;

	alive = true;
	deadtime = 0;
	movingDown = true;
}
cEnemy2::~cEnemy2(void){}

void cEnemy2::SetInitialPosition(int posy)
{
	initialY = posy;
}

void cEnemy2::SetOrientation(bool right)
{
	lookRight = right;
}
void cEnemy2::SetMaxStep(int max) {
	maxStep = max;
}

void cEnemy2::Logic(int *map, int xShotMegaman, int yShotMegaman)
{
	if (IsShooting()) {
		OutputDebugString("Shot Logic \n");
		ShotLogic(true);
	}
	int x, y;
	GetPosition(&x, &y);
	if (GetState() != STATE_DIE) {
		if (IsHited(xShotMegaman, yShotMegaman)) {
			Die();
		}
		else if (y > initialY + maxStep) {
			MoveDown(map);
			OutputDebugString("Shot \n");
			Shot(map,lookRight,true);
		}
		else if (y < initialY - maxStep) {
			MoveUp(map);
			Shot(map, lookRight, true);
		}
		if (movingDown) {
			MoveDown(map);
		}
		else MoveUp(map);
	}
	else {
		deadtime++;
		if (deadtime > 30) alive = false;
	}
}

void cEnemy2::MoveDown(int *map)
{
	int x, y;
	GetPosition(&x, &y);
	y -= STEP_LENGTH;
	SetPosition(x, y);
	movingDown = true;
	if (lookRight) {
		SetState(STATE_WALKRIGHT);
	}
	else SetState(STATE_WALKLEFT);
}

void cEnemy2::MoveUp(int *map)
{
	int x, y;
	GetPosition(&x, &y);
	y += STEP_LENGTH;
	SetPosition(x, y);
	movingDown = false;
	if (lookRight) {
		SetState(STATE_WALKRIGHT);
	}
	else
		SetState(STATE_WALKLEFT);
}

void cEnemy2::Die() {
	SetState(STATE_DIE);
}

bool cEnemy2::IsHited(int xRival, int yRival){
	int x, y;
	GetPosition(&x, &y);
	//35 = w&h && xR+10 = wShot/2 && xY+13 = hShot/2
	if (x + 35 >= xRival - (10) && x + 35 <= xRival + (10)) {
		if (((y + 35 / 2) >= (yRival - 13)) && ((y + 35 / 2) <= (yRival + 13))) return true;
		else return false;
	}
	else return false;
}

void cEnemy2::Draw(int tex_id)
{
	if (alive) {
		float xo, yo, xf, yf;
		float size = 1.0f / 14.0f;
		switch (GetState())
		{
			//1
		case STATE_LOOKLEFT:
			xo = 6.0f * size;	yo = 3.0f*size;
			break;
			//4
		case STATE_LOOKRIGHT:
			xo = 10.0f * size; yo = 3.0f*size;
			break;
			//1..3
		case STATE_WALKLEFT:
			xo = (6.0f * size) - (GetFrame()* size);	yo = 3.0f*size;
			NextFrame(4);
			break;
			//4..6
		case STATE_WALKRIGHT:
			xo = (size * 7) + (GetFrame()* size); yo = 3.0f*size;
			NextFrame(4);
			break;
		case STATE_JUMP_UP_RIGHT:
			xo = (size * 8.0f); yo = 3.0f*size;
			NextFrame(4);
			break;
		case STATE_JUMP_UP_LEFT:
			xo = (size * 5.0f); yo = 3.0f*size;
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
		default:
			xo = 3.0f * size;	yo = 3.0f*size;
			break;
		}
		xf = xo + size;
		yf = yo + size;

		DrawRect(tex_id, xo, yf, xf, yo);
	}
}

void cEnemy2::DrawShot(int tex_id)
{
	float xo, yo, xf, yf;
	xo = 1.0f - (GetFrame()*(1.0f/7.0f));
	NextFrame(7);
	xf = xo - (1.0f / 7.0f);
	yo = 1.0f;
	yf = 0.0f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}
