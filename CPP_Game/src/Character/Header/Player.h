#pragma once
#include "Character.h"
#include "../../Math/Header/Grid.h"
#include "../../Abilities/Header/Rejuvenate.h"
#include "../../Abilities/Header/Fireball.h"
#include "../../Abilities/Header/Placeholder.h"
#include "Enemy.h"

class Grid;

class Player : public Character
{
	private:
		int m_xpNeeded = 50, m_level = 1;
	public:


		Player(int2 position);
		Player();

		int m_curXp = 0;

		void Move(char moveInput, Grid& playArea);
		int2 Move(char moveInput, std::shared_ptr<Grid> grid);

		void SetAfterCombatPosition(int2 newPosition);
		void EndOfCombat();
		bool LevelUpIsReady();
		void LevelUp();
		int GetLevel();
		int GetXpNeeded();
};