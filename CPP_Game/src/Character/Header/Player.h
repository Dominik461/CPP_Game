#pragma once
#include "Character.h"

class Enemy;

class Player : public Character
{
	private:
		int m_heal;

	public:
		Player();
		Player(int hp, int dmg, int heal);
		Player(int hp, int dmg, int heal, int2 position);

		void AttackEnemy(Enemy& enemy);

		int TakeTurn(char action) override;

		void HealSelf();
};