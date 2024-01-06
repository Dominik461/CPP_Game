#include "OpenWorld.h"

Enemy* OpenWorld(std::shared_ptr<World> world)
{
	int2 playerPosition;
	char input;
	bool validInput = false;
	while (true)
	{
		world->PrintRegionChunk();
		do {
			input = _getch();
			if (input != 'w' && input != 'a' && input != 's' && input != 'd')
			{
				validInput = false;
				std::cout << input << " is not a valid move option!" << std::endl;
			}
			else
				validInput = true;
		} while (!validInput);

		std::shared_ptr<Region> region = world->GetCurrentRegion();
		int chunkIndex = world->GetCurrentChunkIndex();
		std::shared_ptr<Chunk> chunk = region->GetChunkAtIndex(chunkIndex);
		std::shared_ptr<Grid> grid = chunk->GetGrid();
	
		if (world != NULL && chunk != NULL && grid != NULL && world->mpCurrentRegionChunk != NULL && chunk->mpNextChunk.size() == 4)
			playerPosition = world->GetPlayerPointer()->Move(input, grid, world->mpCurrentRegionChunk, chunk->mpNextChunk);

		
		if (int2(-2, -2) == playerPosition)
		{
			std::shared_ptr<Region> region = world->GetCurrentRegion();
			int chunkIndex = world->GetCurrentChunkIndex();
			std::shared_ptr<Chunk> chunk = region->GetChunkAtIndex(chunkIndex);
			std::shared_ptr<Grid> grid = chunk->GetGrid();
			grid->SetCharacterAtLocation(world->GetPlayerPointer());
		}
		else if (int2(-1, -1) != playerPosition)
		{
			for (Enemy* pEnemy : chunk->GetEnemyVector())
			{
				if (pEnemy->GetPosition() == playerPosition)
				{
					ClearConsole();
					return pEnemy;
				}
			}
		}
	}
}