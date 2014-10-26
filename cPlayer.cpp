
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	float size = 1.0f / 14.0f;


	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	
			xo = 13.0f * size;	yo = 1.0f*size;
			break;
		//4
		case STATE_LOOKRIGHT:	
			xo = 13.0f * size; yo = 0.0f*size;
			break;
		//1..3
		case STATE_WALKLEFT:	
			xo = (11.0f * size) - (GetFrame()* size);	yo = 1.0f*size;
			NextFrame(11);
			break;
		//4..6
		case STATE_WALKRIGHT:	
			xo = (size*0.0f)+(GetFrame()* size); yo = 0.0f;
			NextFrame(11);
			break;
		case STATE_JUMP_UP_RIGHT:
			xo = (size * 11.0f); yo = 0;
			NextFrame(7);
			break;
		case STATE_JUMP_UP_LEFT:
			xo = (size * 11.0f); yo = size;
			NextFrame(7);
			break;
		case STATE_FALLING_RIGHT:
			xo = (size * 12.0f); yo = 0;
			NextFrame(7);
			break;
		case STATE_FALLING_LEFT:
			xo = (size * 12.0f); yo = size;
			NextFrame(7);
			break;


	}
	xf = xo + size;
	yf = yo + size;

	DrawRect(tex_id,xo,yf,xf,yo);
}
void cPlayer::DrawShot(int tex_id, bool isRight)
{
	float xo, yo, xf, yf;
	xo = 0.0f + (GetFrame()*0.25f); 
	NextFrame(4);
	xf = xo + 0.25f;
	yo = 1.0f;
	yf = 0.0f;
	DrawShotRect(tex_id, xo, yo, xf, yf);
}
