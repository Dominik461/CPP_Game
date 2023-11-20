#include "Header/SelfHeal.h"

SelfHeal::SelfHeal()
	:Ability(3, 12, "Heal")
{}

void SelfHeal::UseAbility(Character * pTarget)
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
			pTarget->m_curHp += this->m_value;
			healAmount = this->m_value;
		}
		//m_logMsg = m_name + " heald for " + std::to_string(healAmount) + " and now has " + std::to_string(m_curHp) + "!";
	}/*
	else
		m_logMsg = "You'r HP are already full!";
		*/
}