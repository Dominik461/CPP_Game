#pragma once
#include "Enemy.h"

class Monolith :public Enemy
{
public:

	const static int  m_spawnChance = 1;
	Monolith(int2 position);
};