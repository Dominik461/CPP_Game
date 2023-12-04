#pragma once
#include "Ability.h"

class Smash : public Ability
{
public:
	Smash();
	std::string UseAbility() override;
};