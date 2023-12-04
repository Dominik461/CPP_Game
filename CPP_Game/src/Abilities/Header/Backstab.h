#pragma once
#include "Ability.h"

class Backstab : public Ability
{
public:
	Backstab();
	std::string UseAbility() override;
};