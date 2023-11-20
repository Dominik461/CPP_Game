#pragma once
#include "Ability.h"

class Fireball : public Ability
{
	Fireball(int cooldown, int value, std::string name);
	void UseAbility(Character* pTarget) override;
};