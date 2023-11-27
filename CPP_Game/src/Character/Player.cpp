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

void Player::AttackEnemy(Character* enemy)
{
	m_logMsg = m_name + " dealt " + std::to_string(m_dmg) + " damage to " + enemy->GetName() + "!";
	enemy->m_curHp -= m_dmg;
}

void Player::TakeTurn(char action, Character* target)
{
	switch (action)
	{
	case 'a':
		AttackEnemy(target);
		break;
	
	case '1':
		m_logMsg = m_abilities.at(0).UseAbility(target, m_name);
		break;
	case '2':
		m_logMsg = m_abilities.at(1).UseAbility(this, m_name);
		break;
	case '3':
		m_logMsg = m_abilities.at(0).UseAbility(target, m_name);
		break;
	
	}
	ReduceAllCooldowns();
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
			playArea.SetCharacterAtLocation(this);
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
			playArea.SetCharacterAtLocation(this);
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
			playArea.SetCharacterAtLocation(this);
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
			playArea.SetCharacterAtLocation(this);
		}
		else
		{
			std::cout << "You are at the edge of the map!" << std::endl;
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