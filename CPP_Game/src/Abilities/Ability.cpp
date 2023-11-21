#include "Header/Ability.h"

Ability::Ability(int cooldown, int value, bool targetSelf, std::string name)
	:m_currentCd(cooldown), m_cd(cooldown), m_value(value), m_name(name), m_targetSelf(targetSelf)
{}

Ability::Ability()
	:m_currentCd(0), m_cd(9999999), m_value(0), m_name("PLACEHOLDER"), m_targetSelf(false)
{}

int Ability::CheckCurrentCooldown()
{
	return m_currentCd;
}

std::string Ability::UseAbility(Character* pTarget, std::string casterName)
{
	std::string logMsg = "";
	if (m_currentCd == m_cd)
	{
		if (m_targetSelf)
		{
			if (pTarget->m_curHp < pTarget->GetMaxHP())
			{
				int healAmount;
				if (pTarget->m_curHp + m_value >= pTarget->GetMaxHP())
				{
					healAmount = pTarget->GetMaxHP() - pTarget->m_curHp;
					pTarget->m_curHp = pTarget->GetMaxHP();
				}
				else
				{
					pTarget->m_curHp += m_value;
					healAmount = m_value;
				}
				logMsg = casterName + " heald for " + std::to_string(healAmount) + " and now has " + std::to_string(pTarget->m_curHp) + "!";
			}
			else
				logMsg = "You'r HP are already full!";
		}
		else
		{
			logMsg = casterName + " casts " + m_name + "! " + pTarget->GetName() + " takes " + std::to_string(m_value) + " damage!";
			pTarget->m_curHp -= m_value;
		}
		m_currentCd = 0;
	}
	return logMsg;
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

bool Ability::IsReady()
{
	return m_currentCd == m_cd;
}