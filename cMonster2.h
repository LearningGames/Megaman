#pragma once

#include "cEnemy2.h"

#define MONSTER_START_CX		6
#define MONSTER_START_CY		2

class cMonster2 : public cEnemy2
{
public:
	cMonster2();
	~cMonster2();

	void Draw(int tex_id);
};
