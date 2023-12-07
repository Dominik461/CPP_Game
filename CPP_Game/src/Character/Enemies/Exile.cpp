#include "../Header/Exile.h"

Exile::Exile(int2 position)
	:Enemy(35, 8, 'E', "Exile", position, Air)
{
	m_xpDrop = 25;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Backstab>());
}