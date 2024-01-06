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
	std::shared_ptr<World> m_world;
	std::string m_line, m_playerSpawnRegion;
	std::shared_ptr<Grid> m_grid;
	std::shared_ptr<Chunk> m_chunk;
	std::ifstream m_inputFile;
	int2 m_playerSpawnLocation;
	int m_counter = 0;
	bool m_endOfTextfile = false, m_debug;

	void GenerateRegion();
	void PrintIfDebug(std::string line);
	void PrintIfDebug(bool line);
	void GenerateEnemiesForChunk(int x, int y, double difficultyMultipier, std::shared_ptr<Region> region, std::string currentRegionChunk);

public:
	WorldGeneration(bool debug);
	std::shared_ptr<World> GenerateWorld();
	
};