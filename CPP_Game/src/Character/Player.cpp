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
	std::cout << "Player dealt " << m_dmg << " damage to Enemy!" << std::endl;;
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
		std::cout << "Player heald for " << healAmount << " and has now " << m_curHp << "!" << std::endl;
	}
}

void Player::Move(char moveInput, Grid& playArea)
{
	std::cout << "Player Input was " << moveInput << "!" << std::endl;
	switch (moveInput)
	{
	case 'w':
		playArea.SetValueAtLocation(m_position, false);
		m_position += int2(0 , 1);
		playArea.SetCharacterAtLocation(*this);
		break;
	case 'a':
		playArea.SetValueAtLocation(m_position, false);
		m_position += int2(-1 , 0);
		playArea.SetCharacterAtLocation(*this);
		break;
	case 's':
		playArea.SetValueAtLocation(m_position, false);
		m_position += int2(0 , -1);
		playArea.SetCharacterAtLocation(*this);
		break;
	case 'd':
		playArea.SetValueAtLocation(m_position, false);
		m_position += int2(1 , 0);
		playArea.SetCharacterAtLocation(*this);
		break;
	}
}