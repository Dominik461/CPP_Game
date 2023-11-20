#pragma once
#include"../../Character/Header/Character.h"

class Ability
{
protected:
	int m_cooldown, m_value;
	std::string m_name;

public:
	Ability(int cooldown, int value, std::string name);
	virtual void UseAbility(Character* pTarget) = 0;
};