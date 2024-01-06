#pragma once
#include "Enemy.h"

class Crawler :public Enemy
{
public:

	const static int  m_spawnChance = 3;
	Crawler(int2 position, double scaler);
};