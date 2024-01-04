#include "World.h"

World::World(std::string playerSpawnRegion, int2 playerSpawnPosition)
	:mPlayerSpawnRegion(playerSpawnRegion), mCurrentRegionChunk(playerSpawnRegion), mPlayerSpawnPosition(playerSpawnPosition)
{}

void World::AddRegion(std::shared_ptr<Region> newRegion)
{
	mRegions.push_back(newRegion);
}

void World::PrintRegionChunk()
{
	std::string region = mCurrentRegionChunk.substr(0, 2);
	for (size_t i = 0; i < mRegions.size(); i++)
	{
		if (mRegions[i]->GetShortForm() == region)
		{
			int ChunkIndex = std::stoi((2 != std::string::npos) ? mCurrentRegionChunk.substr(2 + 1) : "");
			mRegions[i]->PrintChunkAtIndex(ChunkIndex);
		} 
	}
}

void World::SetCurrentRegionChunk(std::string regionChunk)
{
	mCurrentRegionChunk = regionChunk;
}

void World::DebugPrintAllRegions()
{
	std::cout << "Printing whole world!\n";
	for (size_t i = 0; i < mRegions.size(); i++)
	{
		mRegions[i]->DebugPrintAllChunks();
	}
}
