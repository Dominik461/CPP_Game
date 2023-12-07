#pragma once
#include "Enemy.h"

class Yeti : public Enemy 
{
public:
	const static int  m_spawnChance = 2;
	Yeti(int2 position);
};