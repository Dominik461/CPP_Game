#pragma once
#include "src/Math/Int2.h"
#include <vector>

struct GameParameters
{
	int playerDamage;
	int playerHealth;
	int enemyDamage;
	int enemyHealth;

	int2 playerStart;

	unsigned int gridWidth;
	unsigned int gridHeight;

	int enemyCount;
};
