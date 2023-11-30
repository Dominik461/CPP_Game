#include "Header/Heal.h"

Heal::Heal(int cooldown, int value, std::string name, bool selfTarget)
	:Ability(cooldown, value, name, selfTarget)
{}

Heal::Heal()
	:Ability()
{}

std::string Heal::UseAbility()
{
	std::string logMsg = "";
	if (m_currentCd == 0)
	{
		if (m_pTarget->m_curHp < m_pTarget->GetMaxHP())
		{
			int healAmount;
			if (m_pTarget->m_curHp + m_value >= m_pTarget->GetMaxHP())
			{
				healAmount = m_pTarget->GetMaxHP() - m_pTarget->m_curHp;
				m_pTarget->m_curHp = m_pTarget->GetMaxHP();
			}
			else
			{
				m_pTarget->m_curHp += m_value;
				healAmount = m_value;
			}
			logMsg = m_casterName + " heald for " + std::to_string(healAmount) + "HP and now has " + std::to_string(m_pTarget->m_curHp) + "HP!";
		}
		else
			logMsg = "You'r HP are already full!";

		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}