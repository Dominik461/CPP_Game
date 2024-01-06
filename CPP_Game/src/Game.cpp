#include "Game.h"


bool RunGame()
{
	WorldGeneration worldGen = WorldGeneration(false);

	std::shared_ptr<World> world = worldGen.GenerateWorld();
	world->SpawnPlayer();
	Enemy* pCollidedEnemy;
	bool succesfullCombat;

	do
	{
		pCollidedEnemy = OpenWorld(world);
		#pragma region Combat
		//Comabt
		succesfullCombat = Combat(world->GetPlayerPointer(), pCollidedEnemy);
		if (!succesfullCombat)
		{
			world->RemoveAllEnemiesFromMemory();
			break;
		}
		else
		{
			world->RemoveEnemyAtLocationAndMovePlayer(pCollidedEnemy);
		}
		#pragma endregion
	} while (!world->CheckIfAllEnemiesAreDefeated());

	if (succesfullCombat)
	{
		world->PrintRegionChunk();
		std::cout << std::endl;
		std::cout << "All enemies defeated! " << world->GetPlayerPointer()->GetName() << " won!" << std::endl;
		std::cout << "Press any button to close the game..." << std::endl;
		_getch();
	}

	return succesfullCombat;
}