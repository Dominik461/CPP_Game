#pragma once
#include "../Character/Header/Enemy.h"
#include "../Character/Header/Player.h"
#include "../Math/Grid.h"
#include "Combat.h"
#include "../Misc/ConsoleHelpers.h"

Enemy* OpenWorld(Player* player, std::vector<Enemy*> enemies, Grid& playArea);