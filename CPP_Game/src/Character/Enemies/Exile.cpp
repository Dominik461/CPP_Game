#include "../Header/Exile.h"

Exile::Exile(int2 position)
	:Enemy(35, 8, 'E', "Exile", position, Air)
{
	m_xpDrop = 25;
}