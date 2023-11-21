#pragma once
#include "../GameParameters.h"
#include "Character/Header/Enemy.h"
#include "Character/Header/Player.h"
#include "Abilities/Header/Ability.h"
#include "Math/Grid.h"
#include <random>
#include <Windows.h>
#include <conio.h>
#include <iostream>

bool RunGame(const GameParameters& params);
bool Combat(std::vector<char>& playerInputs, Player* player, Enemy* enemy);
void PrintCombat(Player* player, Enemy* enemy, int turnNumber);
void OpenWorld(std::vector<char>& playerInputs, Player* player, Enemy* enemy, Grid playArea);
void ClearConsole();
void moveTo(int x, int y);