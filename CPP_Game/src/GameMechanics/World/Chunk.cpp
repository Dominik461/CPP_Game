#include "Chunk.h"

void Chunk::SetGrid(std::shared_ptr<Grid> grid)
{
	mGrid = grid;
}

std::shared_ptr<Grid> Chunk::GetGrid()
{
	return mGrid;
}

void Chunk::AddEnemy(Enemy* pEnemy)
{
	mpEnemies.push_back(pEnemy);
}

void Chunk::SetCharacter(Character* pCharacter)
{
	mGrid->SetCharacterAtLocation(pCharacter);
}

void Chunk::SetValueAtLocation(int2 position, bool value)
{
	mGrid->SetValueAtLocation(position, value);
}

Enemy* Chunk::GetEnemyAtIndex(int index)
{
	return mpEnemies[index];
}

std::vector<Enemy*> Chunk::GetEnemyVector()
{
	return mpEnemies;
}

void Chunk::PrintGrid(std::string regionName)
{
	mGrid->Print(regionName);
}

void Chunk::DebugPrintGrid()
{
	mGrid->DebugPrint();
}