#include "../Header/Flame of Fury.h"

FlameOfFury::FlameOfFury(int2 position, double scaler)
	:Enemy(32 * scaler, 9 * (1 + (scaler - 1) * 0.5), 'F', "Flame of Fury", position, Fire)
{
	m_xpDrop = 50 * scaler;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Fireball>());
	LearnAbility(std::make_shared<MeteorStrike>());
	SortAbilityPriority();
}