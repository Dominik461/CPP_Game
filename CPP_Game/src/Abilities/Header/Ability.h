#pragma once
#include"../../Character/Header/Character.h"
class Character;
class Ability
{
protected:
	int m_currentCd, m_cd;
	double m_mulitplier;
	std::string m_name, m_logCdMsg;
	bool m_thisTurn = false;
	Character* m_pTarget;
	Character* m_pCaster;

public:
	std::string m_logMsg;
	Ability();
	Ability(int cooldown, double mulitplier, std::string name);
	void SetTargetPointer(Character* pTarget);
	void SetCasterPointer(Character* pCaster);
	virtual std::string UseAbility() = 0;
	int CheckCurrentCooldown();
	int GetCooldown();
	void ReduceCooldown();
	void ResetCooldown();
	bool IsReady();
	std::string GetAbilityMsg();
	std::string GetAbilityName();
};