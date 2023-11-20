#include "Header/Ability.h"

Ability::Ability(int cooldown, int value, std::string name)
	:m_cooldown(cooldown), m_value(value), m_name(name)
{}