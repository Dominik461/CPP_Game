#pragma once
#include "Ability.h"

class Placeholder :public Ability {
public:
	Placeholder();
	std::string UseAbility() override;
};