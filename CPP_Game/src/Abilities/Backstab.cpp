#include "Header/Backstab.h"

Backstab::Backstab()
	:Ability(2, 1.1, "Backstab", false)
{}

std::string Backstab::UseAbility()
{
	int dmg;
	std::string logMsg = "";
	if (m_currentCd == 0)
	{
		if(m_pTarget->m_curHp < m_pTarget->GetMaxHP()*0.3)
			dmg = m_pCaster->GetDamge() * (m_mulitplier*2);
		else
			dmg = m_pCaster->GetDamge() * m_mulitplier;

		logMsg = m_pCaster->GetName() + " casts " + m_name + "! " + m_pTarget->GetName() + " takes " + std::to_string(dmg) + " damage!";
		m_pTarget->m_curHp -= dmg;

		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}