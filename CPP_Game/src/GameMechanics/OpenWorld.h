#pragma once
#include "../Character/Header/Enemy.h"
#include "../Character/Header/Player.h"
#include "../Math/Header/Grid.h"
#include "Combat.h"
#include "World/World.h"
#include "../Misc/ConsoleHelpers.h"
#include <algorithm>

Enemy* OpenWorld(std::shared_ptr<World> world);