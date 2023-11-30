#include "Header/Ability.h"

Ability::Ability(int cooldown, int value, bool targetSelf, std::string name)
	:m_currentCd(0), m_cd(cooldown), m_value(value), m_name(name), m_targetSelf(targetSelf)
{}

Ability::Ability()
	:m_currentCd(0), m_cd(9999999), m_value(0), m_name("PLACEHOLDER"), m_targetSelf(false)
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
	if (!m_thisTurn)
	{
		if (m_currentCd > 0)
		{
			m_currentCd--;
		}
	}
	else
		m_thisTurn = false;
	
}

void Ability::ResetCooldown()
{
	m_currentCd = 0;
}

bool Ability::IsReady()
{
	return m_currentCd == 0;
}

std::string Ability::GetAbilityMsg()
{
	m_logCdMsg = m_name + " Cd: ";
	for (int i = m_cd; i > 0; i--)
	{
		if (i <= m_currentCd)
			m_logCdMsg += "[ ] ";  // Use "[+] " for slots where the cooldown has been used
		else
			m_logCdMsg += "[+] ";  // Use "[] " for remaining cooldown slots
	}
	return m_logCdMsg;
}

std::string Ability::GetAbilityName()
{
	return m_name;
}
