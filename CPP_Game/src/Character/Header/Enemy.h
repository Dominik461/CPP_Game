#pragma once
#include "Character.h"
#include "Player.h"

class Player;

class Enemy : public Character
{
public:
	Enemy();
	Enemy(int hp, int dmg);
	Enemy(int hp, int dmg, int2 position);

	void AttackPlayer(Character* player);
	
	void TakeTurn(char action, Character* target) override;
};