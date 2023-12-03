#include "Header/Character.h"


Character::Character()
	:m_maxHp(0), m_curHp(0),m_dmg(0)
{}

Character::Character(int hp, int dmg)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg)
{}

Character::Character(int hp, int dmg, int2 position)
	:m_maxHp(hp), m_curHp(hp), m_dmg(dmg), m_position(position)
{
	m_abilities.push_back(std::make_shared<Ability>());
	m_abilities.push_back(std::make_shared<Ability>());
	m_abilities.push_back(std::make_shared<Ability>());
}

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

std::shared_ptr<Ability> Character::GetAbilityAtIndex(int index)
{
	return m_abilities.at(index);
}

void Character::InitCombat(Character* pTarget)
{
	for (auto& ability : m_abilities)
	{
		if (ability->GetAbilityName() != "PLACEHOLDER")
		{
			ability->SetCasterName(m_name);
			if (ability->GetSelfTarget())
				ability->SetTargetPointer(this);
			else
				ability->SetTargetPointer(pTarget);
		}
	}
}