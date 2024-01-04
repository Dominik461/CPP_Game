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

public:
	Region(std::string regionName, std::string shortForm);

	void AddChunk(std::shared_ptr<Chunk> newChunk);
	void PrintChunkAtIndex(int index);
	void SetCharacterAtChunkIndex(Character* pCharacter, int index);
	void DebugPrintAllChunks();

	void AddChoiceWeight(int choiceWeight);
	void AddEnemyTypeToChoice(char enemyType);

	std::string GetRegionName();
	std::string GetShortForm();

	int GetChoiceWeightAtIndex(int index);
	char GetEnemyTypeChoiceAtIndex(int index);
	std::shared_ptr<Chunk> GetChunkAtIndex(int index);
	std::vector<char> GetEnemyTypeChoices();


};