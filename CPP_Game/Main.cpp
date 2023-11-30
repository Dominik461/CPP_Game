#include <iostream>
#include "src/Math/Header/Int2.h"
#include "src/Math/Header/Grid.h"
#include "src/Game.h"
#include "GameParameters.h"

int main()
{
	GameParameters params;
	params.playerDamage = 3;
	params.playerHealth = 40;
	params.enemyDamage = 4;
	params.enemyHealth = 30;
	params.playerStart = int2(2, 2);
	params.gridWidth = 12;
	params.gridHeight = 10;
	params.enemyCount = 3;

	RunGame(params);

	return 0;
}
