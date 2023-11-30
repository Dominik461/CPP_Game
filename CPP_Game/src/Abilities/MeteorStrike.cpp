#include "Header/MeteorStrike.h"

MeteorStrike::MeteorStrike(int cooldown, int value, std::string name, bool selfTarget)
	:Ability(cooldown, value, name, selfTarget)
{}

MeteorStrike::MeteorStrike()
	:Ability()
{}

std::string MeteorStrike::UseAbility()
{
	std::string logMsg = "";
	if (m_currentCd == 0)
	{

		logMsg = m_casterName + " casts " + m_name + "! " + m_pTarget->GetName() + " takes " + std::to_string(m_value) + " damage!";
		m_pTarget->m_curHp -= m_value;

		m_currentCd = m_cd;
		m_thisTurn = true;
	}
	return logMsg;
}