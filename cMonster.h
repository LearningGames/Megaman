#pragma once

#include "cEnemy.h"

#define MONSTER_START_CX		6
#define MONSTER_START_CY		2

class cMonster : public cEnemy
{
public:
	cMonster();
	~cMonster();

	void Draw(int tex_id);
};
