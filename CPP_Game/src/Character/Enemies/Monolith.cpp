#include "../Header/Monolith.h"

Monolith::Monolith(int2 position, double scaler)
	:Enemy(90 * scaler, 6 * (1 + (scaler - 1) * 0.5), 'M', "Monolith", position, Earth)
{
	m_xpDrop = 60 * scaler;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());	
	LearnAbility(std::make_shared<Smash>());
	LearnAbility(std::make_shared<Rumble>());
	SortAbilityPriority();
}