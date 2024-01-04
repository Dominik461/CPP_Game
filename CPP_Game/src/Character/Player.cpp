#include "Header/Player.h"

Player::Player(int2 position)
	:Character(45, 8, position)
{
	m_symbole = 'p';
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Fireball>());
	LearnAbility(std::make_shared<Rejuvenate>());
}

Player::Player()
	:Character(45, 8, int2(0, 0))
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
		std::cout << "w was pressd";
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
		std::cout << "a was pressd";
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
		std::cout << "s was pressd";
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
		std::cout << "d was pressd";
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


int2 Player::Move(char moveInput, std::shared_ptr<Grid> grid)
{
	int2 nextPosition;
	switch (moveInput)
	{
	case 'w':
		nextPosition = m_position + int2(0, 1);
		if (grid->LocationInBounds(nextPosition) && !grid->GetValueAtLocation(nextPosition))
		{
			grid->SetValueAtLocation(m_position, false);
			m_position = nextPosition;
			grid->SetCharacterAtLocation(this);
			return int2(-1,-1);
		}
		else
		{
			bool value = grid->GetValueAtLocation(nextPosition);
			Character* occupant = grid->GetCharacterAtLocation(nextPosition);

			if (value && occupant == NULL)
				return int2(-1, -1);
			else if (value && occupant != NULL)
				return nextPosition;
		}
		break;
	case 'a':
		nextPosition = m_position + int2(-1, 0);
		if (grid->LocationInBounds(nextPosition) && !grid->GetValueAtLocation(nextPosition))
		{
			grid->SetValueAtLocation(m_position, false);
			m_position = nextPosition;
			grid->SetCharacterAtLocation(this);
			return int2(-1, -1);
		}
		else
		{
			bool value = grid->GetValueAtLocation(nextPosition);
			Character* occupant = grid->GetCharacterAtLocation(nextPosition);

			if (value && occupant == NULL)
				return int2(-1, -1);
			else if (value && occupant != NULL)
				return nextPosition;
		}
		break;
	case 's':
		nextPosition = m_position + int2(0, -1);
		if (grid->LocationInBounds(nextPosition) && !grid->GetValueAtLocation(nextPosition))
		{
			grid->SetValueAtLocation(m_position, false);
			m_position = nextPosition;
			grid->SetCharacterAtLocation(this);
			return int2(-1, -1);
		}
		else
		{
			bool value = grid->GetValueAtLocation(nextPosition);
			Character* occupant = grid->GetCharacterAtLocation(nextPosition);

			if (value && occupant == NULL)
				return int2(-1, -1);
			else if (value && occupant != NULL)
				return nextPosition;
		}
		break;
	case 'd':
		nextPosition = m_position + int2(1, 0);
		if (grid->LocationInBounds(nextPosition) && !grid->GetValueAtLocation(nextPosition))
		{
			grid->SetValueAtLocation(m_position, false);
			m_position = nextPosition;
			grid->SetCharacterAtLocation(this);
			return int2(-1, -1);
		}
		else
		{
			bool value = grid->GetValueAtLocation(nextPosition);
			Character* occupant = grid->GetCharacterAtLocation(nextPosition);

			if (value && occupant == NULL)
				return int2(-1, -1);
			else if (value && occupant != NULL)
				return nextPosition;
		}
		break;
	}
}


void Player::SetAfterCombatPosition(int2 newPosition)
{
	m_position = newPosition;
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