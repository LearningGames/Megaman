#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		6

//Image identifiers
#define IMG_BLOCKS	0
#define IMG_PLAYER	1
#define IMG_BOSS1	4

#define IMG_MONSTER	1

#define IMG_SHOTRIGHT	2
#define IMG_SHOTLEFT	3
#define IMG_HELISHOT	5


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
