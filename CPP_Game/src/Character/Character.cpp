#include "Header/Character.h"


Character::Character()
	:m_maxHp(0), m_curHp(0),m_dmg(0), m_actionFlags(0)
{}

Character::Character(int hp, int dmg)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg), m_actionFlags(0)
{}

Character::Character(int hp, int dmg, int2 position)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg), m_actionFlags(0), m_position(position)
{}

void Character::SetName(std::string name)
{
	if (m_name == "")
		m_name = name;
}

std::string Character::GetName()
{
	if (m_name != "")
		return m_name;
}

std::string Character::GetLogMsg()
{
	if (m_name != "")
		return m_logMsg;
}

int2 Character::GetPosition()
{
	return m_position;
}

int Character::GetMaxHP()
{
	return m_maxHp;
}

bool Character::Defeated()
{
	if (m_curHp <= 0)
		return true;
	return false;
}