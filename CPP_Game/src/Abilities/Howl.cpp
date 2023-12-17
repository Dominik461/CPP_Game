#include "Header/Howl.h"

Howl::Howl()
	:Ability(5, 1.1, "Howl", true), m_healMultiplier(0.1)
{}

std::string Howl::UseAbility()
{
	std::string logMsg = "";
	if (m_currentCd == 0)
	{
		int dmg = m_pCaster->GetDamge() * m_mulitplier;
				
		logMsg = m_pCaster->GetName() + " casts " + m_name + "! " + m_pTarget->GetName() + " takes " + std::to_string(dmg) + " damage!\n";
		m_pTarget->m_curHp -= dmg;

		if (m_pCaster->m_curHp < m_pCaster->GetMaxHP())
		{
			int healAmount = m_pCaster->GetMaxHP() * m_healMultiplier;
			if (m_pCaster->m_curHp + healAmount >= m_pCaster->GetMaxHP())
			{
				healAmount = m_pCaster->GetMaxHP() - m_pCaster->m_curHp;
				m_pCaster->m_curHp = m_pCaster->GetMaxHP();
				logMsg += m_pCaster->GetName() + " is now at max HP!";
			}
			else
			{
				m_pCaster->m_curHp += healAmount;
				logMsg += m_pCaster->GetName() + " heald for " + std::to_string(healAmount) + "HP and now has " + std::to_string(m_pCaster->m_curHp) + "HP!";
			}

		}
		else
			logMsg += m_pCaster->GetName() + " HP is already full!";


		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}