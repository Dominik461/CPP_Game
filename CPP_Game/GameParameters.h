#pragma once
#include "src/Math/Int2.h"
#include <vector>

struct GameParameters
{
	std::vector<char> playerInputs;
	int playerDamage;
	int playerHeal;
	int playerHealth;
	int enemyDamage;
	int enemyHealth;

	int2 playerStart;
	int2 enemyPosition;

	int gridWidth;
	int gridHeight;

	bool manual;

};
