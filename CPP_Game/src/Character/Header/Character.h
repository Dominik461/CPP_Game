#pragma once
#define ATTACK 0x01
#define ABILITYONE 0x02
#define ABILITYTWO 0x04
#define ABILITYTHREE 0x08
#include "../../Math/Int2.h"
#include "../../Abilities/Header/Ability.h"
#include <iostream>
#include <string>
#include <vector>

class Ability;

class Character
{
	protected:
		int m_dmg, m_maxHp, m_actionFlags, m_newAbilityIndex = 0;
		int2 m_position;
		std::string m_name = "";
		std::string m_logMsg = "";
		std::vector<Ability>m_abilities;

	public:
		int m_curHp;
		Character();
		Character(int hp, int dmg);
		Character(int hp, int dmg, int2 position);
		void LearnAbility(Ability ability);
		void ReduceAllCooldowns();
		void ResetAllCooldowns();
		void SetName(std::string name);
		std::string GetName();
		std::string GetLogMsg();
		virtual void TakeTurn(char action, Character* target) = 0;
		int2 GetPosition();
		int GetMaxHP();
		bool Defeated();
		Ability GetAbilityAtIndex(int index);
};