#pragma once
#include "../../Math/Header/Int2.h"
#include "../../Abilities/Header/Ability.h"
#include <iostream>
#include <string>
#include <vector>

class Ability;

class Character
{
	protected:
		int m_dmg, m_maxHp, m_newAbilityIndex = 0;
		int2 m_position;
		std::string m_name = "";
		std::string m_logMsg = "";
		std::vector<std::shared_ptr<Ability>>m_abilities;

	public:
		int m_curHp;
		Character();
		Character(int hp, int dmg);
		Character(int hp, int dmg, int2 position);
		void LearnAbility(const std::shared_ptr<Ability>& ability);
		void ReduceAllCooldowns();
		void ResetAllCooldowns();
		void SetName(std::string name);
		std::string GetName();
		std::string GetLogMsg();
		virtual void TakeTurn(char action, Character* target) = 0;
		int2 GetPosition();
		int GetMaxHP();
		bool Defeated();
		std::shared_ptr<Ability> GetAbilityAtIndex(int index);
		void InitCombat(Character* pTarget);
};