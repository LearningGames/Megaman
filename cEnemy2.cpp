#include "cEnemy2.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
using namespace std;

cEnemy2::cEnemy2(void)
{
	seq = 0;
	delay = 0;

	jumping = false;
}
cEnemy2::~cEnemy2(void){}

cEnemy2::cEnemy2(int posx, int posy, int width, int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
	initialX = posx;
}
void cEnemy2::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
}

void cEnemy2::SetMaxStep(int max) {
	maxStep = max;
}
void cEnemy2::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
void cEnemy2::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
	initialX = x;
}
void cEnemy2::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cEnemy2::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void cEnemy2::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}
bool cEnemy2::Collides(cEnemyRect2 *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}
bool cEnemy2::CollidesMapWall(int *map, bool right)
{
	int tile_x, tile_y;
	int j;
	int width_tiles, height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if (right)	tile_x += width_tiles;

	for (j = 0; j<height_tiles; j++)
	{
		if (map[tile_x + ((tile_y + j)*SCENE_WIDTH)] != 0)	return true;
	}

	return false;
}

bool cEnemy2::CollidesMapFloor(int *map)
{
	int tile_x, tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if ((x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i = 0;
	while ((i<width_tiles) && !on_base)
	{
		if ((y % TILE_SIZE) == 0)
		{
			if (map[(tile_x + i) + ((tile_y - 1) * SCENE_WIDTH)] != 0)
				on_base = true;
		}
		else
		{
			if (map[(tile_x + i) + (tile_y * SCENE_WIDTH)] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
}

void cEnemy2::GetArea(cEnemyRect2 *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}
void cEnemy2::DrawRect(int tex_id, float xo, float yo, float xf, float yf)
{
	int screen_x, screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h);
	glEnd();
}

void cEnemy2::DrawShotRect(int tex_id, float xo, float yo, float xf, float yf)
{
	int screen_x, screen_y;

	screen_x = xShot;
	screen_y = yShot;

	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + wShot, screen_y);
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + wShot, screen_y + hShot);
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + hShot);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cEnemy2::Move(int *map, int xShot, int yShot)
{
	if (state != STATE_DIE) {
		if (IsHited(xShot, yShot)) {
			Die();
			char s[256];
			sprintf(s, "\n x %d > %d", x, initialX + MAX_STEP);
			OutputDebugStringA(s);
		}
		else if (x > initialX + maxStep) MoveLeft(map);
		else if (x < initialX - maxStep) MoveRight(map);
		else if (state == STATE_WALKLEFT) MoveLeft(map);
		else if (state == STATE_WALKRIGHT) MoveRight(map);
		else MoveRight(map);
	}
}

void cEnemy2::Die() {
	state = STATE_DIE;
}
void cEnemy2::MoveLeft(int *map)
{
	int xaux;

	//Whats next tile?
	/*if ((x % TILE_SIZE) == 0)
	{
	xaux = x;
	x -= STEP_LENGTH;

	if (CollidesMapWall(map, false))
	{
	x = xaux;
	state = STATE_LOOKLEFT;
	}
	}
	//Advance, no problem
	else
	{*/
	x -= STEP_LENGTH;
	if (state != STATE_WALKLEFT)
	{
		if (jumping) state = STATE_JUMP_UP_LEFT;
		else state = STATE_WALKLEFT;
		seq = 0;
		delay = 0;
	}
	//}
}
void cEnemy2::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	/*if ((x % TILE_SIZE) == 0)
	{
	xaux = x;
	x += STEP_LENGTH;

	if (CollidesMapWall(map, true))
	{
	x = xaux;
	state = STATE_LOOKRIGHT;
	}
	}
	//Advance, no problem
	else
	{*/
	x += STEP_LENGTH;

	if (state != STATE_WALKRIGHT)
	{
		//SI SALTA K SALTI
		if (jumping) state = STATE_JUMP_UP_RIGHT;
		else state = STATE_WALKRIGHT;
		seq = 0;
		delay = 0;
	}
	//}
}
void cEnemy2::Stop()
{
	//SI ESTA SALTANT NO ESTA STOP, NO ES MOU PERO SALTA
	if (!jumping){
		switch (state)
		{
		case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
		case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
		case STATE_FALLING_LEFT:state = STATE_LOOKLEFT;		break;
		case STATE_FALLING_RIGHT:state = STATE_LOOKRIGHT;	break;
		case STATE_JUMP_UP_LEFT:state = STATE_LOOKLEFT;		break;
		case STATE_JUMP_UP_RIGHT:state = STATE_LOOKRIGHT;	break;
		}
	}
}
void cEnemy2::Jump(int *map)
{
	if (!jumping)
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
			//SALTA A ALGUN CANTO
			if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_WALKLEFT || state == STATE_FALLING_LEFT)
				state = STATE_JUMP_UP_LEFT;
			else state = STATE_JUMP_UP_RIGHT;
		}
	}
}

bool cEnemy2::IsHited(int xRival, int yRival){
	//35 = w&h && xR+10 = wShot/2 && xY+13 = hShot/2
	if (x + 35 >= xRival - (10) && x + 35 <= xRival + (10)) {
		if (((y + 35 / 2) >= (yRival - 13)) && ((y + 35 / 2) <= (yRival + 13))) return true;
		else return false;
	}
	else return false;
}

void cEnemy2::Shot(int *map, bool isRight)
{
	if (!shooting) {
		if (isRight) isRightShot = true;
		else isRightShot = false;
		shooting = true;
		xShot = x + 35;
		yShot = y + 20;

	}
}

bool cEnemy2::IsShooting() {
	return shooting;
}

bool cEnemy2::IsShootingRight() {
	return isRightShot;
}

void cEnemy2::SetShotDimensions(int width, int height){
	char s[256];
	sprintf(s, "\n ShotDimensions %d %d", width, height);
	OutputDebugStringA(s);
	wShot = width;
	hShot = height;
	sprintf(s, "\n ShotDimensionsSetted %d %d", wShot, hShot);
	OutputDebugStringA(s);
}

void cEnemy2::GetShotPosition(int *xResult, int *yResult) {
	*xResult = xShot;
	*yResult = yShot;
}

void cEnemy2::Logic(int *map)
{
	float alfa;

	if (shooting) {
		shotProgress += SHOT_STEP;
		//We want to know if the shot collides with something
		if (shotProgress >= DIST_SHOT) {
			shooting = false;
			shotProgress = 0;
		}
		else {
			if (isRightShot) xShot += SHOT_STEP;
			else xShot -= SHOT_STEP;
		}
	}

	if (jumping)
	{
		jump_alfa += JUMP_STEP;

		if (jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)(((float)JUMP_HEIGHT) * sin(alfa));

			if (jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
				//ESTA CAIENT DESPRES DE SALTAR
				if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_WALKLEFT || state == STATE_FALLING_LEFT)
					state = STATE_FALLING_LEFT;
				else state = STATE_FALLING_RIGHT;
			}
		}
	}
	else
	{
		//Over floor?
		if (!CollidesMapFloor(map)){
			y -= (2 * STEP_LENGTH);
			//ESTA CAIENT D'ALGUN LLOC SOL SENSE SALTAR
			if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_WALKLEFT || state == STATE_FALLING_LEFT)
				state = STATE_FALLING_LEFT;
			else state = STATE_FALLING_RIGHT;
		}
	}
}

void cEnemy2::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
}
int cEnemy2::GetFrame()
{
	return seq;
}
int cEnemy2::GetState()
{
	return state;
}
void cEnemy2::SetState(int s)
{
	state = s;
}

void cEnemy2::Draw(int tex_id)
{
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
		NextFrame(7);
		break;
		//4..6
	case STATE_WALKRIGHT:
		xo = (size * 7) + (GetFrame()* size); yo = 2.0f*size;
		NextFrame(7);
		break;
	case STATE_JUMP_UP_RIGHT:
		xo = (size * 8.0f); yo = 2.0f*size;
		NextFrame(7);
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
		xo = 1.0f * size;	yo = 2.0f*size;
		break;


	}
	xf = xo + size;
	yf = yo + size;

	DrawRect(tex_id, xo, yf, xf, yo);
}