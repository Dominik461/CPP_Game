#pragma once
#include "Region.h"
#include "../../Character/Header/Player.h"
#include <random>


class World {
	std::vector<std::shared_ptr<Region> > mRegions;
	std::string mCurrentRegionChunk, mPlayerSpawnRegion;
	int2 mPlayerSpawnPosition;
	Player mPlayer;
	Player* mpPlayer;
	void CreatePlayer(int2 spawnPosition);
	bool mAllEnemiesDefeated = false;

public:
	World(std::string playerSpawnRegion, int2 playerSpawnPosition);
	void AddRegion(std::shared_ptr<Region>  newRegion);
	std::shared_ptr<Region> GetCurrentRegion();
	int GetCurrentChunkIndex();
	Player* GetPlayerPointer();
	void SpawnPlayer();
	void PrintRegionChunk();
	void SetCurrentRegionChunk(std::string regionChunk);
	void DebugPrintAllRegions();
	bool CheckIfAllEnemiesAreDefeated();
	void RemoveAllEnemiesFromMemory();
	void RemoveEnemyAtLocationAndMovePlayer(Enemy* pCollidedEnemy);
};