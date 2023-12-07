#pragma once
#include "Character.h"
#include "../../Math/Header/Grid.h"
#include "Enemy.h"

class Grid;

class Player : public Character
{
	public:
		Player();
		Player(int hp, int dmg, int heal);
		Player(int hp, int dmg, int heal, int2 position);
		Player(int hp, int dmg, int2 position);

		void Move(char moveInput, Grid& playArea);

		void EndOfCombat();
};