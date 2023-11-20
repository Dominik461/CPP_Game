#pragma once
#include "Ability.h"

class MeteorStrike: public Ability
{
	MeteorStrike(int cooldown, int value, std::string name);
	void UseAbility(Character* pTarget) override;
};