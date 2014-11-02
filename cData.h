#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		16

//Image identifiers
#define IMG_LEVEL1	0
#define IMG_LEVEL2	8
#define IMG_PLAYER	1
#define IMG_BOSS1	4
#define IMG_BOSS1SHOT	10
#define IMG_BOSS2	9

#define IMG_MONSTER	1

#define IMG_SHOTRIGHT	2
#define IMG_SHOTLEFT	3
#define IMG_HELISHOT	5
#define IMG_GUI_MEGA	6
#define IMG_MENU		7
#define IMG_INST		11
#define IMG_CREDITS		12
#define IMG_GUI_BURST	13
#define IMG_GUI_ROUND	14
#define IMG_INST2		15


class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
