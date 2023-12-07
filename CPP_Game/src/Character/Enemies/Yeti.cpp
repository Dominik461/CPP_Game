#include "../Header/Yeti.h"

Yeti::Yeti(int2 position)
	:Enemy(50, 10, 'Y', "Yeti", position, Water)
{ 
	m_xpDrop = 35;
}