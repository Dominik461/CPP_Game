#pragma once
#include "Ability.h"

class Fireball : public Ability
{
public:
	Fireball();
	std::string UseAbility() override;
};