#pragma once
#include <Windows.h>
#include <conio.h>
#include <chrono>
#include <thread>
#include "../Character/Header/Enemy.h"
#include "../Character/Header/Player.h"
#include "../Misc/ConsoleHelpers.h"


bool Combat(Player* player, Enemy* enemy);
void PrintCombat(Player* player, Enemy* enemy, int turnNumber);
int PrintCombatActions(Player* player, Enemy* enemy);
