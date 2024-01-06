#include "../Header/Exile.h"

Exile::Exile(int2 position, double scaler)
	:Enemy(35 * scaler, 8 * (1 + (scaler - 1) * 0.5), 'E', "Exile", position, Air)
{
	m_xpDrop = 25 * scaler;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Backstab>());
}