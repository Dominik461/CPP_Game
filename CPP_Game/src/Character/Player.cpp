#include "Header/Player.h"

Player::Player(int hp, int dmg, int2 position)
	:Character(hp, dmg, position)
{
	m_symbole = 'p';
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Fireball>());
	LearnAbility(std::make_shared<Rejuvenate>());
}

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

bool Player::LevelUpIsReady()
{
	return m_xpNeeded <= m_curXp;
}

void Player::LevelUp()
{
	std::cout << m_name << " leveled up!" << std::endl;
	m_maxHp *= 1.2;
	m_dmg *= 1.2;
	m_curXp -= m_xpNeeded;
	m_xpNeeded *= 1.3;
	m_level++;
}

int Player::GetLevel()
{
	return m_level;
}

int Player::GetXpNeeded()
{
	return m_xpNeeded;
}