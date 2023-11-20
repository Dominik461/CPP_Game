#include "Header/Ability.h"

Ability::Ability(int cooldown, int value, std::string name)
	:m_currentCd(cooldown), m_cd(cooldown), m_value(value), m_name(name)
{}

int Ability::CheckCurrentCooldown()
{
	return m_currentCd;
}

int Ability::GetCooldown()
{
	return m_cd;
}

void Ability::ReduceCooldown()
{
	if (m_currentCd < m_cd)
		m_currentCd++;
}
