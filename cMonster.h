#pragma once

#include "cBicho.h"

#define MONSTER_START_CX		6
#define MONSTER_START_CY		2

class cMonster : public cBicho
{
public:
	cMonster();
	~cMonster();

	void Draw(int tex_id);
};
