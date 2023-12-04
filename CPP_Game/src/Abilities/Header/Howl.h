#pragma once
#include "Ability.h"

class Howl : public Ability
{
private:
	double m_healMultiplier;
public:
	Howl();
	std::string UseAbility() override;
};