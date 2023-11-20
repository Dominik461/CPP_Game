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

void Player::AttackEnemy(Enemy& enemy)
{
	m_logMsg = "Player dealt " + std::to_string(m_dmg) + " damage to Enemy!";
	enemy.m_curHp -= m_dmg;
}

int Player::TakeTurn(char action)
{
	m_actionFlags = 0;
	switch (action)
	{
	case 'h':
		m_actionFlags |= HEALFLAG;
		break;
	
	case 'a':
		m_actionFlags |= ATTACKFLAG;
	}
	return m_actionFlags;
}

void Player::HealSelf()
{
	if (m_curHp < m_maxHp)
	{
		int healAmount;
		if (m_curHp + m_heal >= m_maxHp)
		{
			healAmount = m_maxHp - m_curHp;
			m_curHp = m_maxHp;
		}
		else
		{
			m_curHp += m_heal;
			healAmount = m_heal;
		}
		m_logMsg = m_name + " heald for " + std::to_string(healAmount) + " and now has " + std::to_string(m_curHp) + "!";
	}
	else
		m_logMsg = "You'r HP are already full!";

	
}

void Player::Move(char moveInput, Grid& playArea)
{
	std::cout << m_name <<" Input was " << moveInput << "!" << std::endl;
	switch (moveInput)
	{
	case 'w':		
		if (playArea.LocationInBounds(m_position + int2(0, 1)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(0, 1);
			playArea.SetCharacterAtLocation(*this);
		}
		else
		{
			std::cout << "You are at the edge of the map!" << std::endl;
		}
		break;
	case 'a':
		if (playArea.LocationInBounds(m_position + int2(-1, 0)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(-1, 0);
			playArea.SetCharacterAtLocation(*this);
		}
		else
		{
			std::cout << "You are at the edge of the map!" << std::endl;
		}
		break;
	case 's':
		if (playArea.LocationInBounds(m_position + int2(0, -1)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(0, -1);
			playArea.SetCharacterAtLocation(*this);
		}
		else
		{
			std::cout << "You are at the edge of the map!" << std::endl;
		}
		break;
	case 'd':
		if (playArea.LocationInBounds(m_position + int2(1, 0)))
		{
			playArea.SetValueAtLocation(m_position, false);
			m_position += int2(1, 0);
			playArea.SetCharacterAtLocation(*this);
		}
		else
		{
			std::cout << "You are at the edge of the map!" << std::endl;
		}
		break;
	}
}