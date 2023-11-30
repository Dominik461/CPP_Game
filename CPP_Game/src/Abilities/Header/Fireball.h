#pragma once
#include "Ability.h"

class Fireball : public Ability
{
public:
	Fireball();
	Fireball(int cooldown, int value, std::string name);
	std::string UseAbility(Character* pTarget, std::string casterName) override;
};