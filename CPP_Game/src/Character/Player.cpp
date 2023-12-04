#include "Header/Player.h"

Player::Player()
	:Character(), m_heal(0)
{}

Player::Player(int hp, int dmg, int heal)
	:Character(hp, dmg), m_heal(heal)
{}

Player::Player(int hp, int dmg, int heal, int2 position)
	:Character(hp, dmg, position), m_heal(heal)
{}

Player::Player(int hp, int dmg, int2 position)
	:Character(hp, dmg, position), m_heal(0)
{}

void Player::Move(char moveInput, Grid& playArea)
{
	switch (moveInput)
	{
	case 'w':		
		if (playArea.LocationInBounds(m_position + int2(0, 1)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(0, 1);
			playArea.SetCharacterAtLocation(this);
		}
		else
		{
			m_logMsg = "You are at the edge of the map!";
		}
		break;
	case 'a':
		if (playArea.LocationInBounds(m_position + int2(-1, 0)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(-1, 0);
			playArea.SetCharacterAtLocation(this);
		}
		else
		{
			m_logMsg = "You are at the edge of the map!";
		}
		break;
	case 's':
		if (playArea.LocationInBounds(m_position + int2(0, -1)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(0, -1);
			playArea.SetCharacterAtLocation(this);
		}
		else
		{
			m_logMsg = "You are at the edge of the map!";
		}
		break;
	case 'd':
		if (playArea.LocationInBounds(m_position + int2(1, 0)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(1, 0);
			playArea.SetCharacterAtLocation(this);
		}
		else
		{
			m_logMsg = "You are at the edge of the map!";
		}
		break;
	}
}

void Player::EndOfCombat()
{
	if (m_curHp + (m_maxHp / 2) >= m_maxHp)
		m_curHp = m_maxHp;
	else
		m_curHp += (m_maxHp / 2);
	ResetAllCooldowns();
}