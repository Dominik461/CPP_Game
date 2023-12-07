#include "../Header/Flame of Fury.h"

FlameOfFury::FlameOfFury(int2 position)
	:Enemy(32, 9, 'F', "Flame of Fury", position, Fire)
{
	m_xpDrop = 50;
}