#include "cEnemy2.h"
#include "cScene.h"
#include "Globals.h"

cEnemy2::cEnemy2(void)
{
	movingDown = true;
}
cEnemy2::~cEnemy2(void){}

void cEnemy2::SetInitialPosition(int posy)
{
	initialY = posy;
}

void cEnemy2::SetMaxStep(int max) {
	maxStep = max;
}

bool cEnemy2::Logic(int *map, cRect *playerShot,int level)
{
	boolean result = false;
	if (IsShooting()) {
		ShotLogic(ENEMY2,map);
	}
	int x, y;
	GetPosition(&x, &y);
	if (IsAlive() && GetState() != STATE_DIE) {
		if (Collides(playerShot)) {
			Die();
			result = true;
		}
		else if (y > initialY + maxStep) {		
			MoveDown(map);
			Shot(map,IsLookingRight());
		}
		else if (y < initialY - maxStep) {
			MoveUp(map);
			Shot(map, IsLookingRight());
		}
		else if (movingDown) {
			MoveDown(map);
		}
		else MoveUp(map);
	}
	else if (IsAlive()) {
		int time = GetDeadTime();
		++time;
		SetDeadTime(time);
		if (GetDeadTime() > DEAD_TIME) SetAlive(false);
	}
	return result;
}

void cEnemy2::MoveDown(int *map)
{
	int x, y;
	GetPosition(&x, &y);
	y -= STEP_LENGTH;
	SetPosition(x, y);
	movingDown = true;
	
	if (IsLookingRight()) {
		if (GetState() != STATE_WALKRIGHT) SetState(STATE_WALKRIGHT);
	}
	else if (GetState() != STATE_WALKLEFT)SetState(STATE_WALKLEFT);
}

void cEnemy2::MoveUp(int *map)
{
	int x, y;
	GetPosition(&x, &y);
	y += STEP_LENGTH;
	SetPosition(x, y);
	movingDown = false;
	if (IsLookingRight()) {
		if (GetState() != STATE_WALKRIGHT) SetState(STATE_WALKRIGHT);
	}
	else if (GetState() != STATE_WALKLEFT)SetState(STATE_WALKLEFT);
}

void cEnemy2::Die() {
	SetState(STATE_DIE);
}

void cEnemy2::Draw(int tex_id)
{
	if (IsAlive()) {
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
		case STATE_DIE:
			xo = (size * 6) - (GetFrame()* size);	yo = 4.0f*size;
			NextFrame(7);
			break;
		default:
			break;
		}
		xf = xo + size;
		yf = yo + size;

		DrawRect(tex_id, xo, yf, xf, yo);
	}
}

void cEnemy2::NextShotFrame(int max)
{
	delayShot++;
	if (delayShot == FRAME_DELAY)
	{
		seqShot++;
		seqShot %= max;
		delayShot = 0;
	}
}

void cEnemy2::DrawShot(int tex_id)
{
	float xo, yo, xf, yf;
	xo = 1.0f - (GetFrame()*(1.0f/7.0f));
	NextShotFrame(7);
	xf = xo - (1.0f / 7.0f);
	yo = 1.0f;
	yf = 0.0f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}
