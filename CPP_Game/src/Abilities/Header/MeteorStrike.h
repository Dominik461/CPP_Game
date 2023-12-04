#pragma once
#include "Ability.h"

class MeteorStrike : public Ability
{
public:
	MeteorStrike();
	std::string UseAbility() override;
};