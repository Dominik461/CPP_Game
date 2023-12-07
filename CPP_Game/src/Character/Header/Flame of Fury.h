#pragma once
#include "Enemy.h"

class FlameOfFury :public Enemy
{
public:

	const static int  m_spawnChance = 2;
	FlameOfFury(int2 position);
};