#include "Header/Character.h"

Character::Character()
	:m_maxHp(0), m_curHp(0),m_dmg(0)
{}

Character::Character(int hp, int dmg)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg)
{}

Character::Character(int hp, int dmg, int2 position)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg), m_position(position)
{}

void Character::LearnAbility(const std::shared_ptr<Ability>& ability)
{
	if (m_newAbilityIndex < 3)
	{
		m_abilities.at(m_newAbilityIndex) = ability;
	}
		
	else
	{
		m_newAbilityIndex = 0;
		m_abilities.at(m_newAbilityIndex) = ability;
	}
	m_newAbilityIndex++;
		
}

void Character::ReduceAllCooldowns()
{
	
	for (auto& ability : m_abilities)
	{
		ability->ReduceCooldown();
	}
	
}

void Character::ResetAllCooldowns()
{
	for (auto& ability : m_abilities)
	{
		ability->ResetCooldown();
	}
}

void Character::SetName(std::string name)
{
	if (m_name == "")
		m_name = name;
}

std::string Character::GetName()
{
	if (m_name != "")
		return m_name;
	else
		return "PLACEHOLDER NAME";
}

std::string Character::GetLogMsg()
{
	std::string temp = m_logMsg;
	m_logMsg = "";
	return temp;
}

void Character::TakeTurn(char action)
{
	switch (action)
	{
	case 'a':
		AttackTarget();
		break;

	case '1':
		m_logMsg = m_abilities.at(0)->UseAbility();
		break;
	case '2':
		m_logMsg = m_abilities.at(1)->UseAbility();
		break;
	case '3':
		m_logMsg = m_abilities.at(2)->UseAbility();
		break;

	}
	ReduceAllCooldowns();
}

void Character::AttackTarget()
{
	m_logMsg = m_name + " dealt " + std::to_string(m_dmg) + " damage to " + m_pTarget->GetName() + "!";
	m_pTarget->m_curHp -= m_dmg;
}

int2 Character::GetPosition()
{
	return m_position;
}

int Character::GetMaxHP()
{
	return m_maxHp;
}

char Character::GetSymbol()
{
	return m_symbole;
}

bool Character::Defeated()
{
	if (m_curHp <= 0)
		return true;
	return false;
}

std::shared_ptr<Ability> Character::GetAbilityAtIndex(int index)
{
	return m_abilities.at(index);
}

int Character::GetDamge()
{
	return m_dmg;
}

void Character::InitCombat(Character* pTarget)
{
	m_pTarget = pTarget;
	for (auto& ability : m_abilities)
	{
		if (ability->GetAbilityName() != "PLACEHOLDER")
		{
			ability->SetCasterPointer(this);
			ability->SetTargetPointer(pTarget);
		}
	}
}

void Character::FillAbilitiesWithPlaceholders(std::shared_ptr<Ability> placeholder)
{
	m_abilities.push_back(placeholder);
	m_abilities.push_back(placeholder);
	m_abilities.push_back(placeholder);
}
