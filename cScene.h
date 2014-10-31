#pragma once

#include "cTexture.h"

#define SCENE_Xo		(2*TILE_SIZE)
#define SCENE_Yo		TILE_SIZE
#define SCENE_WIDTH		199
#define SCENE_HEIGHT	15

#define FILENAME		"MAPA01"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);

	bool LoadLevel(int level);
	void Draw(int tex_id);
	int *GetMap();
	int *GetCollisionMap();

private:
	int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int collisionMap[SCENE_WIDTH * SCENE_HEIGHT];  //collision scene
	int id_DL;								//actual level display list
};
