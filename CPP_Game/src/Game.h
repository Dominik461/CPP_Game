#pragma once
#include "../GameParameters.h"
#include "Character/Header/Enemy.h"
#include "Character/Header/Player.h"
#include "Abilities/Header/Ability.h"
#include "Abilities/Header/Fireball.h"
#include "Abilities/Header/Heal.h"
#include "Abilities/Header/MeteorStrike.h"
#include "Math/Header/Grid.h"
#include "GameMechanics/Combat.h"
#include "GameMechanics/OpenWorld.h"
#include "Misc/ConsoleHelpers.h"
#include <random>
#include <iostream>

bool RunGame(const GameParameters& params);