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

void cEnemy2::Logic(int *map, cRect *playerShot)
{
	if (IsShooting()) {
		ShotLogic(true);
	}
	int x, y;
	GetPosition(&x, &y);
	char sAux[256];
	sprintf(sAux, "stateLogic %d \n", GetState());
	OutputDebugString(sAux);
	if (alive && GetState() != STATE_DIE) {
		if (Collides(playerShot)) {
			OutputDebugString("Die \n");
			Die();
		}
		else if (y > initialY + maxStep) {		
			MoveDown(map);
			Shot(map,lookRight);
		}
		else if (y < initialY - maxStep) {
			MoveUp(map);
			Shot(map, lookRight);
		}
		else if (movingDown) {
			MoveDown(map);
		}
		else MoveUp(map);
	}
	else if (alive) {
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
	if (lookRight) {
		if (GetState() != STATE_WALKRIGHT) SetState(STATE_WALKRIGHT);
	}
	else if (GetState() != STATE_WALKLEFT)SetState(STATE_WALKLEFT);
}

void cEnemy2::Die() {
	OutputDebugString("SetStateEnemy \n");
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
	OutputDebugString("Draw \n");
	if (alive) {
		float xo, yo, xf, yf;
		float size = 1.0f / 14.0f;
		char s[256];
		sprintf(s, "state %d", GetState());
		OutputDebugString(s);
		switch (GetState())
		{
			//1
		case STATE_LOOKLEFT:
			OutputDebugString("LOOK_LEFT \n");
			xo = 6.0f * size;	yo = 3.0f*size;
			break;
			//4
		case STATE_LOOKRIGHT:
			OutputDebugString("LOOK_RIGHT \n");
			xo = 10.0f * size; yo = 3.0f*size;
			break;
			//1..3
		case STATE_WALKLEFT:
			OutputDebugString("WALK_LEFT \n");
			xo = (6.0f * size) - (GetFrame()* size);	yo = 3.0f*size;
			NextFrame(4);
			break;
			//4..6
		case STATE_WALKRIGHT:
			OutputDebugString("WALK_RIGHT \n");
			xo = (size * 7) + (GetFrame()* size); yo = 3.0f*size;
			NextFrame(4);
			break;
		case STATE_DIE:
			OutputDebugString("STATE_DIE");
			xo = (size * 6) - (GetFrame()* size);	yo = 4.0f*size;
			NextFrame(7);
			break;
		default:
			OutputDebugString("default");
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
