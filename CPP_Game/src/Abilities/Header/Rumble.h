#pragma once
#include "Ability.h"

class Rumble : public Ability
{
public:
	Rumble();
	std::string UseAbility() override;
};