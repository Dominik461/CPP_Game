#pragma once
#include"../../Character/Header/Character.h"
class Character;
class Ability
{
protected:
	int m_currentCd, m_cd, m_value;
	std::string m_name, m_casterName, m_logCdMsg;
	bool m_thisTurn = false, m_selfTarget;
	Character* m_pTarget;

public:
	std::string m_logMsg;
	Ability();
	Ability(int cooldown, int value, std::string name, bool selfTarget);
	void SetTargetPointer(Character* pTarget);
	void SetCasterName(std::string casterName);
	virtual std::string UseAbility();
	int CheckCurrentCooldown();
	int GetCooldown();
	void ReduceCooldown();
	void ResetCooldown();
	bool IsReady();
	bool GetSelfTarget();
	std::string GetAbilityMsg();
	std::string GetAbilityName();
};