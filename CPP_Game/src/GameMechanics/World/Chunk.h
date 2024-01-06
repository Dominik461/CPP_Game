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
	//Will be in the order of N,E,S,W
	std::vector<std::shared_ptr<std::string>> mpNextChunk;
	
	void SetGrid(std::shared_ptr<Grid> grid);
	std::shared_ptr<Grid> GetGrid();
	void AddEnemy(Enemy* pEnemy);
	void SetCharacter(Character* pCharacter);
	void SetValueAtLocation(int2 position, bool value);
	Enemy* GetEnemyAtIndex(int index);
	std::vector<Enemy*> GetEnemyVector();
	void PrintGrid(std::string regionName);
	void DebugPrintGrid();
};