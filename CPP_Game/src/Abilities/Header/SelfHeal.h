#pragma once
#include "Ability.h"

struct SelfHeal : public Ability
{
public:
	SelfHeal();
	void UseAbility(Character* pTarget) override;
};