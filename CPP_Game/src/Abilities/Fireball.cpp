#include "Header/Fireball.h"

Fireball::Fireball()
	:Ability(3, 1.5, "Fireball", false)
{}

std::string Fireball::UseAbility()
{
	std::string logMsg = "";
	if (m_currentCd == 0)
	{
		int dmg = m_pCaster->GetDamge() * m_mulitplier;
		logMsg = m_pCaster->GetName() + " casts " + m_name + "! " + m_pTarget->GetName() + " takes " + std::to_string(dmg) + " damage!";
		m_pTarget->m_curHp -= dmg;
		
		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}