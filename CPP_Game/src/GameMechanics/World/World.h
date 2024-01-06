#pragma once
#include "Region.h"
#include "../../Character/Header/Player.h"
#include <random>


class World {
	std::vector<std::shared_ptr<Region> > m_regions;
	std::string m_playerSpawnRegion;
	int2 m_playerSpawnPosition;
	Player m_player;
	Player* mp_player;
	void CreatePlayer(int2 spawnPosition);
	bool m_allEnemiesDefeated = false;

public:
	std::shared_ptr<std::string> mp_currentRegionChunk;

	World(std::string playerSpawnRegion, int2 playerSpawnPosition);
	void AddRegion(std::shared_ptr<Region>  newRegion);
	std::shared_ptr<Region> GetCurrentRegion();
	int GetCurrentChunkIndex();
	Player* GetPlayerPointer();

	void SpawnPlayer();
	void PrintRegionChunk();
	void SetCurrentRegionChunk(std::shared_ptr<std::string> regionChunk);
	void DebugPrintAllRegions();
	bool CheckIfAllEnemiesAreDefeated();
	void RemoveAllEnemiesFromMemory();
	void RemoveEnemyAtLocationAndMovePlayer(Enemy* pCollidedEnemy);
};