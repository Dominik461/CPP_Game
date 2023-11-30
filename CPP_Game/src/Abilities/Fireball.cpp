#include "Header/Fireball.h"

Fireball::Fireball(int cooldown, int value, std::string name)
	:Ability(cooldown, value, false, name)
{}

Fireball::Fireball()
	:Ability()
{}

std::string Fireball::UseAbility(Character* pTarget, std::string casterName)
{
	std::string logMsg = "";
	if (m_currentCd == 0)
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
		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}