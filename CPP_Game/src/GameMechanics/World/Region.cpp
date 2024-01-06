#include "Region.h"

Region::Region(std::string regionName, std::string shortForm)
	:mRegionName(regionName), mShortForm(shortForm)
{}

void Region::AddChunk(std::shared_ptr<Chunk> newChunk)
{
	mChunks.push_back(newChunk);
}

void Region::PrintChunkAtIndex(int index)
{
	mChunks[index]->PrintGrid(mRegionName);
}

void Region::SetCharacterAtChunkIndex(Character* pCharacter, int index)
{
	mChunks[index]->SetCharacter(pCharacter);
}

void Region::DebugPrintAllChunks()
{
	for (size_t i = 0; i < mChunks.size(); i++)
	{
		std::cout << "Current chunk: " << mShortForm << i << std::endl;
		mChunks[i]->DebugPrintGrid();
	}
}

void Region::AddChoiceWeight(int choiceWeight)
{
	mChoiceWeights.push_back(choiceWeight);
}

void Region::AddEnemyTypeToChoice(char enemyType)
{
	mChoices.push_back(enemyType);
}

std::string Region::GetRegionName()
{
	return mRegionName;
}

std::string Region::GetShortForm()
{
	return mShortForm;
}

void Region::SetDifficulty(double scale)
{
	mDifficultyScale = scale;
}

double Region::GetDifficulty()
{
	return mDifficultyScale;
}

int Region::GetChoiceWeightAtIndex(int index)
{
	return mChoiceWeights[index];
}

char Region::GetEnemyTypeChoiceAtIndex(int index)
{
	return mChoices[index];
}

std::shared_ptr<Chunk> Region::GetChunkAtIndex(int index)
{
	return mChunks[index];
}

std::vector<char> Region::GetEnemyTypeChoices()
{
	return mChoices;
}

bool Region::CheckIfAllEnemiesAreDefeatedInRegion()
{
	std::vector<Enemy*> pEnemies;
	for (std::shared_ptr<Chunk> chunk : mChunks)
	{
		pEnemies = chunk->GetEnemyVector();
		if (pEnemies.size() > 0)
			return false;
	}

	return true;
}

void Region::RemoveAllEnemiesFromMemoryInRegion()
{
	std::vector<Enemy*> pEnemies;
	for (std::shared_ptr<Chunk> chunk : mChunks)
	{
		pEnemies = chunk->GetEnemyVector();
		for (Enemy* pEnemy : pEnemies)
		{
			delete pEnemy;
		}
		pEnemies.clear();			
	}
}

int2 Region::RemoveEnemyAtLocationInRegion(int chunkIndex, Enemy* pCollidedEnemy)
{
	std::vector<Enemy*> pEnemies;
	std::shared_ptr<Chunk> chunk = mChunks[chunkIndex];
	int2 newPlayerPosition = pCollidedEnemy->GetPosition();

	pEnemies = chunk->GetEnemyVector();

	chunk->SetValueAtLocation(pCollidedEnemy->GetPosition(), false);

	auto enemyToRemove = std::find(pEnemies.begin(), pEnemies.end(), pCollidedEnemy);
	delete* enemyToRemove;
	pEnemies.erase(enemyToRemove);

	return newPlayerPosition;
}
