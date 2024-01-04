#pragma once
#include "Region.h"

class World {
	std::vector<std::shared_ptr<Region> > mRegions;
	std::string mCurrentRegionChunk, mPlayerSpawnRegion;
	int2 mPlayerSpawnPosition;

public:
	World(std::string playerSpawnRegion, int2 playerSpawnPosition);
	void AddRegion(std::shared_ptr<Region>  newRegion);
	void PrintRegionChunk();
	void SetCurrentRegionChunk(std::string regionChunk);
	void DebugPrintAllRegions();
};