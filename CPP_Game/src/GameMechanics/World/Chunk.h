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

public:
	std::string mNextRegionN, mNextRegionE, mNextRegionS, mNextRegionW;
		
	void SetGrid(std::shared_ptr<Grid> grid);
	void AddEnemy(Enemy* pEnemy);
	Enemy* GetEnemyAtIndex(int index);
	std::vector<Enemy*> GetEnemyVector();
	void PrintGrid();
	void DebugPrintGrid();
};