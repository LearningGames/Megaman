#include "cBoss1.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
using namespace std;

cBoss1::cBoss1(void)
{
	seq = 0;
	delay = 0;

	jumping = false;
}
cBoss1::~cBoss1(void){}

cBoss1::cBoss1(int posx, int posy, int width, int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBoss1::SetPosition(int posx, int posy)
{
	x = posx;
	y = posy;
}
void cBoss1::GetPosition(int *posx, int *posy)
{
	*posx = x;
	*posy = y;
}
void cBoss1::SetTile(int tx, int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBoss1::GetTile(int *tx, int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBoss1::SetWidthHeight(int width, int height)
{
	w = width;
	h = height;
}
void cBoss1::GetWidthHeight(int *width, int *height)
{
	*width = w;
	*height = h;
}
bool cBoss1::Collides(cBossRect *rc)
{
	return ((x>rc->left) && (x + w<rc->right) && (y>rc->bottom) && (y + h<rc->top));
}
bool cBoss1::CollidesMapWall(int *map, bool right)
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

bool cBoss1::CollidesMapFloor(int *map)
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

void cBoss1::GetArea(cBossRect *rc)
{
	rc->left = x;
	rc->right = x + w;
	rc->bottom = y;
	rc->top = y + h;
}
void cBoss1::DrawRect(int tex_id, float xo, float yo, float xf, float yf)
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

	glDisable(GL_TEXTURE_2D);
}

void cBoss1::DrawShotRect(int tex_id, float xo, float yo, float xf, float yf)
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

void cBoss1::Stop()
{
	//SI ESTA SALTANT NO ESTA STOP, NO ES MOU PERO SALTA
	if (!jumping){
		switch (state)
		{
		case STATE_FALLING_LEFT:state = STATE_LOOKLEFT;		break;
		case STATE_FALLING_RIGHT:state = STATE_LOOKRIGHT;	break;
		case STATE_JUMP_UP_LEFT:state = STATE_LOOKLEFT;		break;
		case STATE_JUMP_UP_RIGHT:state = STATE_LOOKRIGHT;	break;
		}
	}
}
void cBoss1::Jump(int *map)
{
	if (!jumping)
	{
		if (CollidesMapFloor(map))
		{
			jumping = true;
			jump_alfa = 0;
			jump_y = y;
			//SALTA A ALGUN CANTO
			if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_FALLING_LEFT)
				state = STATE_JUMP_UP_LEFT;
			else state = STATE_JUMP_UP_RIGHT;
		}
	}
}

/*bool cBoss1::IsHited(cEnemy Enemies[], int size){
	//35 = w&h && xR+10 = wShot/2 && xY+13 = hShot/
	for (int i = 0; i < size; ++i) {
		int xRival, yRival;
		Enemies[i].GetPosition(&xRival, &yRival);
		if (x >= xRival - (32 / 2) && x <= xRival + (32 / 2)) {
			if (((y + 35 / 2) >= (yRival - 35 / 2)) && ((y + 35 / 2) <= (yRival + 35 / 2))) return true;
			else return false;
		}
		else return false;
	}
}*/

void cBoss1::Hited()
{
	if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_FALLING_LEFT) {
	}
	else {
		x -= STEP_LENGTH;
		state = STATE_HITED;
	}

}

void cBoss1::Shot(int *map, bool isRight)
{
	if (!shooting) {
		if (isRight) isRightShot = true;
		else isRightShot = false;
		shooting = true;
		xShot = x + 40;
		yShot = y + 20;

	}
}

bool cBoss1::IsShooting() {
	return shooting;
}

bool cBoss1::IsShootingRight() {
	return isRightShot;
}

void cBoss1::SetShotDimensions(int width, int height){
	char s[256];
	sprintf(s, "\n ShotDimensions %d %d", width, height);
	OutputDebugStringA(s);
	wShot = width;
	hShot = height;
	sprintf(s, "\n ShotDimensionsSetted %d %d", wShot, hShot);
	OutputDebugStringA(s);
}

void cBoss1::GetShotPosition(int *xResult, int *yResult) {
	*xResult = xShot;
	*yResult = yShot;
}

bool cBoss1::ShotCollidesWall(int *map)
{
	int xo, yo, xf, yf, tile_x, tile_y;

	xo = xShot;
	yo = yShot;
	xf = xShot + wShot;
	yf = yShot + hShot;

	if (isRightShot)
	{
		//xf e yf
		tile_x = xf / TILE_SIZE;
		tile_y = yf / TILE_SIZE;
		char s[256];
		sprintf(s, "map [%d] = %d", tile_x + tile_y*(199 / TILE_SIZE), map[tile_x + tile_y*(199 / TILE_SIZE)]);
		OutputDebugStringA(s);
		if (map[tile_x + tile_y*(199 / TILE_SIZE)] == 17) return true;
	}
	else
	{
		tile_x = xo / TILE_SIZE;
		tile_y = yo / TILE_SIZE;
		char s[256];
		sprintf(s, "map [%d] = %d", tile_x + tile_y*(199 / TILE_SIZE), map[tile_x + tile_y*(199 / TILE_SIZE)]);
		OutputDebugStringA(s);
		if (map[tile_x + tile_y*(199 / TILE_SIZE)] == 17) return true;
	}
	OutputDebugStringA("return false");
	return false;
}

void cBoss1::Logic(int *map)
{
	float alfa;

	

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
				if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_FALLING_LEFT)
					state = STATE_FALLING_LEFT;
				else state = STATE_FALLING_RIGHT;
			}
		}
	}
	else if (shooting) {
		shotProgress += SHOT_STEP;
		//We want to know if the shot collides with something
		if (/*ShotCollidesWall(map) ||*/ shotProgress >= DIST_SHOT) {
			shooting = false;
			shotProgress = 0;
		}
		else {
			if (isRightShot) xShot += SHOT_STEP;
			else xShot -= SHOT_STEP;
		}
	}
	else
	{
		//Over floor?
		if (!CollidesMapFloor(map)){
			y -= (2 * STEP_LENGTH);
			//ESTA CAIENT D'ALGUN LLOC SOL SENSE SALTAR
			if (state == STATE_LOOKLEFT || state == STATE_JUMP_UP_LEFT || state == STATE_FALLING_LEFT)
				state = STATE_FALLING_LEFT;
			else state = STATE_FALLING_RIGHT;
		}
	}
}

void cBoss1::NextFrame(int max)
{
	delay++;
	if (delay == FRAME_DELAY)
	{
		seq++;
		seq %= max;
		delay = 0;
	}
}
int cBoss1::GetFrame()
{
	return seq;
}
int cBoss1::GetState()
{
	return state;
}
void cBoss1::SetState(int s)
{
	state = s;
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
		xo = 0.0f; yo = 1.0f*sizey;
		NextFrame(7);
		break;
	case STATE_FALLING_RIGHT:
		xo = 0.0f; yo = 1.0f*sizey;
		NextFrame(7);
		break;
	case STATE_FALLING_LEFT:
		xo = 0.0f; yo = 1.0f*sizey;
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

