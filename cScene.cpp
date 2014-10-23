#include "cScene.h"
#include "Globals.h"

int size = 1 / 16;

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i, j, px, py;
	int tile;
	float coordx_tile, coordy_tile;

	res = true;

	if (level<10) sprintf(file, "%s%s", (char *)FILENAME, (char *)FILENAME_EXT);
	else		 sprintf(file, "%s%d%s", (char *)FILENAME, level, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = SCENE_HEIGHT - 1; j >= 0; j--)
	{
		px = SCENE_Xo;
		py = SCENE_Yo + (j*TILE_SIZE);

		for (i = 0; i<SCENE_WIDTH; i++)
		{
			fscanf(fd, "%d", &tile);
			if (tile == 0)
			{
				//Tiles must be != 0 !!!
				map[(j*SCENE_WIDTH) + i] = 0;
			}
			else
			{
				tile -= 1;
				map[(j*SCENE_WIDTH) + i] = tile ;

				coordx_tile = (map[(j*SCENE_WIDTH)+i])%7;
				coordy_tile = (map[(j*SCENE_WIDTH) + i]) / 7;
				
				float size_g = 1.0f / 7.0f;

				float size_x = coordx_tile * size_g;
				float size_y = coordy_tile * size_g;
				

				//BLOCK_SIZE = 24, FILE_SIZE = 64
				// 24 / 64 = 0.375
				glTexCoord2f(size_x, size_y + size_g);	glVertex2i(px, py);
				glTexCoord2f(size_x + size_g, size_y + size_g);	glVertex2i(px + BLOCK_SIZE, py);
				glTexCoord2f(size_x + size_g, size_y);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
				glTexCoord2f(size_x, size_y);	glVertex2i(px, py + BLOCK_SIZE);
			}
			px += TILE_SIZE;
		}
		fscanf(fd, "%d", &tile); //pass enter
	}

	glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}