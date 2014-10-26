#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"
#include <stdio.h>
using namespace std;

cBicho::cBicho(void)
{
	seq=0;
	delay=0;

	jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}
bool cBicho::Collides(cRect *rc)
{
	return ((x>rc->left) && (x+w<rc->right) && (y>rc->bottom) && (y+h<rc->top));
}
bool cBicho::CollidesMapWall(int *map,bool right)
{
	int ax, ay;
	GetTile(&ax, &ay);
	char s[256];
	sprintf(s, "ELS TILES %d,%d,%d\n",  map[ax - 1 + (ay*SCENE_WIDTH)], map[ax + 1 + (ay*SCENE_WIDTH)]
		, map[ax  + (ay*SCENE_WIDTH)]
		);
	OutputDebugStringA(s);

	if (right){
		if (map[ax + 2 + (ay*SCENE_WIDTH)] == 0) return false;
		else return true;
	}
	else{
		if (map[ax - 2 + (ay*SCENE_WIDTH)] == 0) return false;
		else return true;
	}
	return true;
	/*int tile_x,tile_y;
	int j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE;
	height_tiles = h / TILE_SIZE;

	if(right)	tile_x += width_tiles;
	
	for(j=0;j<height_tiles;j++)
	{
		if(map[ tile_x + ((tile_y)*SCENE_WIDTH) ] != 0)	return false;
	}
	
	return true;*/
}

bool cBicho::CollidesMapFloor(int *map)
{
	/*
	int tile_x,tile_y;
	int width_tiles;
	bool on_base;
	int i;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;

	width_tiles = w / TILE_SIZE;
	if( (x % TILE_SIZE) != 0) width_tiles++;

	on_base = false;
	i=0;
	while((i<width_tiles) && !on_base)
	{
		if( (y % TILE_SIZE) == 0 )
		{
			if(map[ (tile_x + i) + ((tile_y - 1) * SCENE_WIDTH) ] != 0)
				on_base = true;
		}
		else
		{
			if(map[ (tile_x + i) + (tile_y * SCENE_WIDTH) ] != 0)
			{
				y = (tile_y + 1) * TILE_SIZE;
				on_base = true;
			}
		}
		i++;
	}
	return on_base;
	*/
}

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x + SCENE_Xo;
	screen_y = y + SCENE_Yo;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::DrawShotRect(int tex_id, float xo, float yo, float xf, float yf)
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

void cBicho::MoveLeft(int *map)
{
	
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= STEP_LENGTH;

		if(  CollidesMapWall(map,false))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= STEP_LENGTH;
		if(state != STATE_WALKLEFT)
		{
			if (jumping) state = STATE_JUMP_UP_LEFT;
			else state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
	
}
void cBicho::MoveRight(int *map)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += STEP_LENGTH;

		if(CollidesMapWall(map,true))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += STEP_LENGTH;

		if(state != STATE_WALKRIGHT)
		{
			//SI SALTA K SALTI
			if (jumping) state = STATE_JUMP_UP_RIGHT;
			else state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::Stop()
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
void cBicho::Jump(int *map)
{
	if(!jumping)
	{
		if(CollidesMapFloor(map))
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

bool cBicho::IsHited(cEnemy Enemies[], int size){
	//35 = w&h && xR+10 = wShot/2 && xY+13 = hShot/
	for (int i = 0; i < size; ++i) {
		int xRival, yRival;
		Enemies[i].GetPosition(&xRival, &yRival);
		if (x + 35 >= xRival - (35) && x + 35 <= xRival + (35)) {
			if (((y + 35 / 2) >= (yRival - 35/2)) && ((y + 35 / 2) <= (yRival + 35/2))) return true;
			else return false;
		}
		else return false;
	}
}

void cBicho::Shot(int *map, bool isRight)
{
	if (!shooting) {
		if (isRight) isRightShot = true;
		else isRightShot = false;
		shooting = true;
		xShot = x + 35;
		yShot = y + 20;
		
	}
}

bool cBicho::IsShooting() {
	return shooting;
}

bool cBicho::IsShootingRight() {
	return isRightShot;
}

void cBicho::SetShotDimensions(int width, int height){
	char s[256];
	sprintf(s, "\n ShotDimensions %d %d", width, height);
	OutputDebugStringA(s);
	wShot = width;
	hShot = height;
	sprintf(s, "\n ShotDimensionsSetted %d %d", wShot, hShot);
	OutputDebugStringA(s);
}

void cBicho::GetShotPosition(int *xResult, int *yResult) {
	*xResult = xShot;
	*yResult = yShot;
}

bool cBicho::ShotCollidesWall(int *map)
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

void cBicho::Logic(int *map)
{
	float alfa;

	if (shooting) {
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

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
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

void cBicho::NextFrame(int max)
{
	delay++;
	if(delay == FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}