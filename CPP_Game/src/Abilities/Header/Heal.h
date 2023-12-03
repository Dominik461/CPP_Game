#pragma once
#include "Ability.h"

class Heal : public Ability
{
public:
	Heal();
	Heal(int cooldown, int value, std::string name, bool selfTarget);
	std::string UseAbility() override;
};