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
