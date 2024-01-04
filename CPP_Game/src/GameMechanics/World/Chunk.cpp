#include "Chunk.h"

void Chunk::SetGrid(std::shared_ptr<Grid> grid)
{
	mGrid = grid;
}

void Chunk::AddEnemy(Enemy* pEnemy)
{
	std::cout << "New enemy added: " << pEnemy->GetName() << "\n";
	mpEnemies.push_back(pEnemy);
}

Enemy* Chunk::GetEnemyAtIndex(int index)
{
	return mpEnemies[index];
}

std::vector<Enemy*> Chunk::GetEnemyVector()
{
	return mpEnemies;
}

void Chunk::PrintGrid()
{
	mGrid->Print();
}

void Chunk::DebugPrintGrid()
{
	mGrid->DebugPrint();
}