#pragma once
#include "../GameParameters.h"
#include "Character/Header/Enemy.h"
#include "Character/Header/Player.h"
#include "Math/Grid.h"
#include <random>

bool RunGame(const GameParameters& params);
bool Combat(const GameParameters& params, Player& player, Enemy& enemy);