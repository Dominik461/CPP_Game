#pragma once
#include "Enemy.h"

class Exile :public Enemy
{
public:

	const static int  m_spawnChance = 3;
	Exile(int2 position, double scaler);
};