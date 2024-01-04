#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "../../Math/Header/Grid.h"
#include "../../Character/Header/AllCharacters.h"


class Chunk
{
	std::shared_ptr<Grid> mGrid;
	std::vector<Enemy*> mpEnemies;
	Player* mpPlayer;

public:
	std::string mNextRegionN, mNextRegionE, mNextRegionS, mNextRegionW;

	void SetGrid(std::shared_ptr<Grid> grid);
	std::shared_ptr<Grid> GetGrid();
	void AddEnemy(Enemy* pEnemy);
	void SetCharacter(Character* pCharacter);
	Enemy* GetEnemyAtIndex(int index);
	std::vector<Enemy*> GetEnemyVector();
	void PrintGrid(std::string regionName);
	void DebugPrintGrid();
};