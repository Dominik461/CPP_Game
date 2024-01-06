#pragma once
#include "../../Math/Header/Grid.h"
#include "Chunk.h"
#include <string>

class Region
{
	std::string m_regionName, m_shortForm;
	std::vector<std::shared_ptr<Chunk>> m_chunks;
	std::vector<int> m_choiceWeights;
	std::vector<char> m_choices;
	double m_difficultyScale = 0;

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