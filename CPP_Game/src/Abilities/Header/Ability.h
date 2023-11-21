#pragma once
#include"../../Character/Header/Character.h"
class Character;
class Ability
{
protected:
	int m_currentCd, m_cd, m_value;
	std::string m_name;
	bool m_targetSelf = false;

public:
	std::string m_logMsg;
	Ability();
	Ability(int cooldown, int value, bool targetSelf,std::string name);
	std::string UseAbility(Character* pTarget, std::string casterName);
	int CheckCurrentCooldown();
	int GetCooldown();
	void ReduceCooldown();
	bool IsReady();
};