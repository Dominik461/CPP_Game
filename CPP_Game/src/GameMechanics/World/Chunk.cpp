#include "Chunk.h"

void Chunk::SetGrid(std::shared_ptr<Grid> grid)
{
	m_grid = grid;
}

std::shared_ptr<Grid> Chunk::GetGrid()
{
	return m_grid;
}

void Chunk::AddEnemy(Enemy* pEnemy)
{
	mp_enemies.push_back(pEnemy);
}

void Chunk::SetCharacter(Character* pCharacter)
{
	m_grid->SetCharacterAtLocation(pCharacter);
}

void Chunk::SetValueAtLocation(int2 position, bool value)
{
	m_grid->SetValueAtLocation(position, value);
}

Enemy* Chunk::GetEnemyAtIndex(int index)
{
	return mp_enemies[index];
}

std::vector<Enemy*>& Chunk::GetEnemyVector()
{
	return mp_enemies;
}

void Chunk::PrintGrid(std::string regionName, std::string playerLevel)
{
	m_grid->Print(regionName, playerLevel);
}

void Chunk::DebugPrintGrid()
{
	m_grid->DebugPrint();
}