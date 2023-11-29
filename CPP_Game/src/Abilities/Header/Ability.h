#pragma once
#include"../../Character/Header/Character.h"
class Character;
class Ability
{
protected:
	int m_currentCd, m_cd, m_value;
	std::string m_name, m_logCdMsg;
	bool m_targetSelf = false, m_thisTurn = false;

public:
	std::string m_logMsg;
	Ability();
	Ability(int cooldown, int value, bool targetSelf,std::string name);
	std::string UseAbility(Character* pTarget, std::string casterName);
	int CheckCurrentCooldown();
	int GetCooldown();
	void ReduceCooldown();
	void ResetCooldown();
	bool IsReady();
	std::string GetAbilityMsg();
	std::string GetAbilityName();
};