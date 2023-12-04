#pragma once
#include "Ability.h"

class Rejuvenate : public Ability
{
public:
	Rejuvenate();
	std::string UseAbility() override;
};