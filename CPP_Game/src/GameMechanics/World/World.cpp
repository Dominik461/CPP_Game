#include "World.h"

World::World(std::string playerSpawnRegion, int2 playerSpawnPosition)
	:mPlayerSpawnRegion(playerSpawnRegion), mpCurrentRegionChunk(std::make_shared<std::string>(playerSpawnRegion)), mPlayerSpawnPosition(playerSpawnPosition)
{
	CreatePlayer(mPlayerSpawnPosition);
}

void World::CreatePlayer(int2 spawnPosition)
{
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Guenter", "Otto" };

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);

	mPlayer = Player(spawnPosition);
	mpPlayer = &mPlayer;
	mpPlayer->SetName(playerNames.at(distribution(gen)));
}


void World::AddRegion(std::shared_ptr<Region> newRegion)
{
	mRegions.push_back(newRegion);
}

void World::SpawnPlayer()
{
	std::shared_ptr<Region> region = GetCurrentRegion();

	region->SetCharacterAtChunkIndex(mpPlayer, GetCurrentChunkIndex());
}

std::shared_ptr<Region> World::GetCurrentRegion()
{
	std::string region = mpCurrentRegionChunk->substr(0, 2);
	for (size_t i = 0; i < mRegions.size(); i++)
	{
		if (mRegions[i]->GetShortForm() == region)
		{
			return mRegions[i];
		}
	}
}

int World::GetCurrentChunkIndex()
{
	std::shared_ptr<Region> region = GetCurrentRegion();
	return std::stoi(mpCurrentRegionChunk->substr(2, 1));
}

Player* World::GetPlayerPointer()
{
	return mpPlayer;
}

void World::PrintRegionChunk()
{
	std::shared_ptr<Region> region = GetCurrentRegion();
	
	region->PrintChunkAtIndex(GetCurrentChunkIndex(), mpPlayer->GetLevelAsString());

}

void World::DebugPrintAllRegions()
{
	std::cout << "Printing whole world!\n";
	for (size_t i = 0; i < mRegions.size(); i++)
	{
		mRegions[i]->DebugPrintAllChunks();
	}
}

bool World::CheckIfAllEnemiesAreDefeated()
{
	for (std::shared_ptr<Region> region : mRegions)
	{
		if (!region->CheckIfAllEnemiesAreDefeatedInRegion())
			return false;
	}

	return true;
}

void World::RemoveAllEnemiesFromMemory()
{
	for (std::shared_ptr<Region> region : mRegions)
	{
		region->RemoveAllEnemiesFromMemoryInRegion();
	}
}

void World::RemoveEnemyAtLocationAndMovePlayer(Enemy* pCollidedEnemy)
{
	std::shared_ptr<Region> region = GetCurrentRegion();

	region->GetChunkAtIndex(GetCurrentChunkIndex())->SetValueAtLocation(mpPlayer->GetPosition(), false);

	int2 newPlayerPos = region->RemoveEnemyAtLocationInRegion(GetCurrentChunkIndex(), pCollidedEnemy);

	mpPlayer->SetAfterCombatPosition(newPlayerPos);
	
	region->GetChunkAtIndex(GetCurrentChunkIndex())->SetCharacter(mpPlayer);

}
