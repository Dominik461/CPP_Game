#include "Region.h"

Region::Region(std::string regionName, std::string shortForm)
	:m_regionName(regionName), m_shortForm(shortForm)
{}

void Region::AddChunk(std::shared_ptr<Chunk> newChunk)
{
	m_chunks.push_back(newChunk);
}

void Region::PrintChunkAtIndex(int index, std::string playerLevel)
{
	m_chunks[index]->PrintGrid(m_regionName, playerLevel);
}

void Region::SetCharacterAtChunkIndex(Character* pCharacter, int index)
{
	m_chunks[index]->SetCharacter(pCharacter);
}

void Region::DebugPrintAllChunks()
{
	for (size_t i = 0; i < m_chunks.size(); i++)
	{
		std::cout << "Current chunk: " << m_shortForm << i << std::endl;
		m_chunks[i]->DebugPrintGrid();
	}
}

void Region::AddChoiceWeight(int choiceWeight)
{
	m_choiceWeights.push_back(choiceWeight);
}

void Region::AddEnemyTypeToChoice(char enemyType)
{
	m_choices.push_back(enemyType);
}

std::string Region::GetRegionName()
{
	return m_regionName;
}

std::string Region::GetShortForm()
{
	return m_shortForm;
}

void Region::SetDifficulty(double scale)
{
	m_difficultyScale = scale;
}

double Region::GetDifficulty()
{
	return m_difficultyScale;
}

int Region::GetChoiceWeightAtIndex(int index)
{
	return m_choiceWeights[index];
}

char Region::GetEnemyTypeChoiceAtIndex(int index)
{
	return m_choices[index];
}

std::shared_ptr<Chunk> Region::GetChunkAtIndex(int index)
{
	return m_chunks[index];
}

std::vector<char> Region::GetEnemyTypeChoices()
{
	return m_choices;
}

bool Region::CheckIfAllEnemiesAreDefeatedInRegion()
{
	std::vector<Enemy*> pEnemies;
	for (std::shared_ptr<Chunk> chunk : m_chunks)
	{
		pEnemies = chunk->GetEnemyVector();
		if (pEnemies.size() > 0)
			return false;
	}

	return true;
}

void Region::RemoveAllEnemiesFromMemoryInRegion()
{
	for (std::shared_ptr<Chunk>& chunk : m_chunks)
	{
		std::vector<Enemy*>& pEnemies = chunk->GetEnemyVector();
		for (Enemy* pEnemy : pEnemies)
		{
			delete pEnemy;
		}
		pEnemies.clear();			
	}
}

int2 Region::RemoveEnemyAtLocationInRegion(int chunkIndex, Enemy* pCollidedEnemy)
{
	
	std::shared_ptr<Chunk>& chunk = m_chunks[chunkIndex];
	int2 newPlayerPosition = pCollidedEnemy->GetPosition();

	std::vector<Enemy*>& pEnemies = chunk->GetEnemyVector();

	chunk->SetValueAtLocation(pCollidedEnemy->GetPosition(), false);

	auto enemyToRemove = std::find(pEnemies.begin(), pEnemies.end(), pCollidedEnemy);
	delete *enemyToRemove;
	pEnemies.erase(enemyToRemove);

	return newPlayerPosition;
}
