#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include "../Math/Header/Grid.h"
#include "./World/World.h"
#include "./World/World.h"
#include "../Character/Header/AllCharacters.h"
#include <random>
#include <iostream>

class WorldGeneration
{
	std::shared_ptr<World> mWorld;
	std::string mLine, mPlayerSpawnRegion;
	std::shared_ptr<Grid> mGrid;
	std::shared_ptr<Chunk> mChunk;
	std::ifstream mInputFile;
	int2 mPlayerSpawnLocation;
	int mCounter = 0;
	bool mEndOfTextfile = false, mDebug;

	void GenerateRegion();
	void PrintIfDebug(std::string line);
	void PrintIfDebug(bool line);
	void GenerateEnemiesForChunk(int x, int y, int difficultyMultipier, std::shared_ptr<Region> region, std::string currentRegionChunk);

public:
	WorldGeneration(bool debug);
	std::shared_ptr<World> GenerateWorld();
	
};