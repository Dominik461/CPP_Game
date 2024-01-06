#pragma once
#include "../../Math/Header/Grid.h"
#include "Chunk.h"
#include <string>

class Region
{
	std::string mRegionName, mShortForm;
	std::vector<std::shared_ptr<Chunk>> mChunks;
	std::vector<int> mChoiceWeights;
	std::vector<char> mChoices;
	double mDifficultyScale = 0;

public:
	Region(std::string regionName, std::string shortForm);

	void AddChunk(std::shared_ptr<Chunk> newChunk);
	void PrintChunkAtIndex(int index, std::string playerLevel);
	void SetCharacterAtChunkIndex(Character* pCharacter, int index);
	void DebugPrintAllChunks();

	void AddChoiceWeight(int choiceWeight);
	void AddEnemyTypeToChoice(char enemyType);

	std::string GetRegionName();
	std::string GetShortForm();
	
	void SetDifficulty(double scale);
	double GetDifficulty();
	int GetChoiceWeightAtIndex(int index);
	char GetEnemyTypeChoiceAtIndex(int index);
	std::shared_ptr<Chunk> GetChunkAtIndex(int index);
	std::vector<char> GetEnemyTypeChoices();

	bool CheckIfAllEnemiesAreDefeatedInRegion();
	void RemoveAllEnemiesFromMemoryInRegion();
	int2 RemoveEnemyAtLocationInRegion(int chunkIndex, Enemy* pCollidedEnemy);
};