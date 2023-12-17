#pragma once
#include "Character.h"
#include "../../Math/Header/Grid.h"
#include "Enemy.h"

class Grid;

class Player : public Character
{
	public:

		Player(int2 position);

		void Move(char moveInput, Grid& playArea);

		void EndOfCombat();
};