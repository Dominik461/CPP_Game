#include "../Header/Yeti.h"

Yeti::Yeti(int2 position, double scaler)
	:Enemy(50 * scaler, 10 * (1 + (scaler - 1) * 0.5), 'Y', "Yeti", position, Water)
{ 
	m_xpDrop = 35 * scaler;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Smash>());
	LearnAbility(std::make_shared<Howl>());
	SortAbilityPriority();
}