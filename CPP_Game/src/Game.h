#pragma once
#include "../GameParameters.h"
#include "Character/Header/AllCharacters.h"
#include "Abilities/Header/Ability.h"
#include "Abilities/Header/AllAbilites.h"
#include "Math/Header/Grid.h"
#include "GameMechanics/Combat.h"
#include "GameMechanics/OpenWorld.h"
#include "Misc/ConsoleHelpers.h"
#include <random>
#include <iostream>

bool RunGame(const GameParameters& params);
Enemy* ChooseRandomEnemy(int2 position);