#pragma once
#include "Character.h"

class Player;

class Enemy : public Character
{
public:
	Enemy();
	Enemy(int hp, int dmg);
	Enemy(int hp, int dmg, int2 position);

	void AttackPlayer(Player& player);
	
	int TakeTurn(char action) override;
};