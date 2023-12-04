#pragma once
#include "Ability.h"

class Claw : public Ability
{
public:
	Claw();
	std::string UseAbility() override;
};