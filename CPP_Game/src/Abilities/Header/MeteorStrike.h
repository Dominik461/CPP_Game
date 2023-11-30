#pragma once
#include "Ability.h"

class MeteorStrike : public Ability
{
public:
	MeteorStrike();
	MeteorStrike(int cooldown, int value, std::string name, bool selfTarget);
	std::string UseAbility() override;
};