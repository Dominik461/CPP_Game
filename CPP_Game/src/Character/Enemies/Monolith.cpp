#include "../Header/Monolith.h"

Monolith::Monolith(int2 position)
	:Enemy(90, 6, 'M', "Monolith", position, Earth)
{
	m_xpDrop = 60;
}