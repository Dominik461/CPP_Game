#include "../Header/Flame of Fury.h"

FlameOfFury::FlameOfFury(int2 position)
	:Enemy(32, 9, 'F', "Flame of Fury", position, Fire)
{
	m_xpDrop = 50;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Fireball>());
	LearnAbility(std::make_shared<MeteorStrike>());
}