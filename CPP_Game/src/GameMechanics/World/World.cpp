#include "World.h"

World::World(std::string playerSpawnRegion, int2 playerSpawnPosition)
	:m_playerSpawnRegion(playerSpawnRegion), mp_currentRegionChunk(std::make_shared<std::string>(playerSpawnRegion)), m_playerSpawnPosition(playerSpawnPosition)
{
	CreatePlayer(m_playerSpawnPosition);
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

	m_player = Player(spawnPosition);
	mp_player = &m_player;
	mp_player->SetName(playerNames.at(distribution(gen)));
}


void World::AddRegion(std::shared_ptr<Region> newRegion)
{
	m_regions.push_back(newRegion);
}

void World::SpawnPlayer()
{
	std::shared_ptr<Region> region = GetCurrentRegion();

	region->SetCharacterAtChunkIndex(mp_player, GetCurrentChunkIndex());
}

std::shared_ptr<Region> World::GetCurrentRegion()
{
	std::string region = mp_currentRegionChunk->substr(0, 2);
	for (size_t i = 0; i < m_regions.size(); i++)
	{
		if (m_regions[i]->GetShortForm() == region)
		{
			return m_regions[i];
		}
	}
}

int World::GetCurrentChunkIndex()
{
	std::shared_ptr<Region> region = GetCurrentRegion();
	return std::stoi(mp_currentRegionChunk->substr(2, 1));
}

Player* World::GetPlayerPointer()
{
	return mp_player;
}

void World::PrintRegionChunk()
{
	std::shared_ptr<Region> region = GetCurrentRegion();
	
	region->PrintChunkAtIndex(GetCurrentChunkIndex(), mp_player->GetLevelAsString());

}

void World::DebugPrintAllRegions()
{
	std::cout << "Printing whole world!\n";
	for (size_t i = 0; i < m_regions.size(); i++)
	{
		m_regions[i]->DebugPrintAllChunks();
	}
}

bool World::CheckIfAllEnemiesAreDefeated()
{
	for (std::shared_ptr<Region> region : m_regions)
	{
		if (!region->CheckIfAllEnemiesAreDefeatedInRegion())
			return false;
	}

	return true;
}

void World::RemoveAllEnemiesFromMemory()
{
	for (std::shared_ptr<Region> region : m_regions)
	{
		region->RemoveAllEnemiesFromMemoryInRegion();
	}
}

void World::RemoveEnemyAtLocationAndMovePlayer(Enemy* pCollidedEnemy)
{
	std::shared_ptr<Region> region = GetCurrentRegion();

	region->GetChunkAtIndex(GetCurrentChunkIndex())->SetValueAtLocation(mp_player->GetPosition(), false);

	int2 newPlayerPos = region->RemoveEnemyAtLocationInRegion(GetCurrentChunkIndex(), pCollidedEnemy);

	mp_player->SetAfterCombatPosition(newPlayerPos);
	
	region->GetChunkAtIndex(GetCurrentChunkIndex())->SetCharacter(mp_player);

}
