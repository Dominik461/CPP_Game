#pragma once
#include "Ability.h"

class Fireball : public Ability
{
public:
	Fireball();
	Fireball(int cooldown, int value, std::string name, bool selfTarget);
	std::string UseAbility() override;
};