#include "Header/Ability.h"

Ability::Ability(int cooldown, double multiplier, std::string name, bool hasHeal)
	:m_currentCd(0), m_cd(cooldown), m_mulitplier(multiplier), m_name(name), m_hasHeal(hasHeal)
{}

Ability::Ability()
	:m_currentCd(0), m_cd(9999999), m_mulitplier(0), m_name("PLACEHOLDER"), m_hasHeal(false)
{}

void Ability::SetTargetPointer(Character* pTarget)
{
	if (pTarget != NULL)
		m_pTarget = pTarget;
}


void Ability::SetCasterPointer(Character* pCaster)
{
	if (pCaster != NULL)
		m_pCaster = pCaster;
}

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