#pragma once
#include "../GameParameters.h"
#include "Character/Header/Enemy.h"
#include "Character/Header/Player.h"
#include "Math/Grid.h"
#include <random>
#include <Windows.h>
#include <conio.h>

bool RunGame(const GameParameters& params);
bool Combat(std::vector<char>& playerInputs, bool manual, Player& player, Enemy& enemy);
void OpenWorld(std::vector<char>& playerInputs, bool manual, Player& player, Enemy& enemy, Grid playArea);
void ClearConsole();