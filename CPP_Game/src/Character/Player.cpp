#include "Header/Player.h"
#include "../Misc/ConsoleHelpers.h"

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

int2 Player::Move(char moveInput, std::shared_ptr<Grid>& grid, std::shared_ptr<std::string>& currentChunk, std::vector<std::shared_ptr<std::string>>& nextChunk)
{
	int2 nextPosition;

	switch (moveInput)
	{
	case 'w':		
		nextPosition = m_position + int2(0, 1);
		break;
	case 'a':
		nextPosition = m_position + int2(-1, 0);

		break;
	case 's':
		nextPosition = m_position + int2(0, -1);
		break;
	case 'd':		
		nextPosition = m_position + int2(1, 0);
		break;
	}

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
		{
			return int2(-1, -1);
		}
		else if (!value)
		{
			grid->SetValueAtLocation(m_position, false);
			
			if (nextPosition.y == grid->GetHeight())
			{
				currentChunk = nextChunk[0];
				m_position = int2(m_position.x, 0);
			}
			else if(nextPosition.x == grid->GetWidth())
			{
				currentChunk = nextChunk[1];
				m_position = int2(0, m_position.y);
			}
			if (nextPosition.y == -1)
			{
				currentChunk = nextChunk[2];
				m_position = int2(m_position.x, grid->GetHeight()-1);
			}
			else if (nextPosition.x == -1)
			{
				currentChunk = nextChunk[3];
				m_position = int2(grid->GetWidth()-1, m_position.y);
			}
			
			return int2(-2, -2);
		}
		else if (value && occupant != NULL)
			return nextPosition;
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
	ClearConsole();
	std::cout << m_name << " leveled up!" << std::endl;
	std::cout << "Hp increased from: " << m_maxHp << " to " << m_maxHp*1.2 << std::endl;
	std::cout << "Damage increased from: " << m_dmg << " to " << std::round(m_dmg * 1.2) << std::endl;
	std::cout << "Xp needed for next level: " << m_xpNeeded * 1.3 << std::endl;
	std::cout << std::endl;
	std::cout << "Press any button to continue..." << std::endl;
	m_maxHp *= 1.2;
	m_dmg *= 1.2;
	m_curXp -= m_xpNeeded;
	m_xpNeeded *= 1.3;
	m_level++;
	EndOfCombat();
	_getch();
}

int Player::GetLevel()
{
	return m_level;
}

std::string Player::GetLevelAsString()
{
	return "Level: " + std::to_string(m_level) + "(" + std::to_string(m_curXp) + "|" + std::to_string(m_xpNeeded) + ")";
}

int Player::GetXpNeeded()
{
	return m_xpNeeded;
}