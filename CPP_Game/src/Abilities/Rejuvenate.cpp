#include "Header/Rejuvenate.h"

Rejuvenate::Rejuvenate()
	:Ability(4, 0.3, "Rejuvenate", true)
{}

std::string Rejuvenate::UseAbility()
{
	std::string logMsg = "";
	if (m_currentCd == 0)
	{
		if (m_pCaster->m_curHp < m_pCaster->GetMaxHP())
		{
			int healAmount = m_pCaster->GetMaxHP() * m_mulitplier;
			if (m_pCaster->m_curHp + healAmount >= m_pCaster->GetMaxHP())
			{
				healAmount = m_pCaster->GetMaxHP() - m_pCaster->m_curHp;
				m_pCaster->m_curHp = m_pCaster->GetMaxHP();
				logMsg = m_pCaster->GetName() + " is now at max HP!";
			}
			else
			{
				m_pCaster->m_curHp += healAmount;
				logMsg = m_pCaster->GetName() + " heald for " + std::to_string(healAmount) + "HP and now has " + std::to_string(m_pCaster->m_curHp) + "HP!";
			}
			
		}
		else
			logMsg = m_pCaster->GetName() + " HP is already full!";

		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}