#include "../Header/Enemy.h"


Enemy::Enemy()
	:Character()
{}

Enemy::Enemy(int hp, int dmg, char symbole, std::string name, int2 position, Element element)
	:Character(hp, dmg, position), m_element(element)
{
	m_symbole = symbole;
	m_name = name;
}

Enemy::Enemy(int hp, int dmg, int2 position)
	:Character(hp, dmg, position)
{
	m_symbole = 'e';
}

void Enemy::InitCombat(Character* pTarget)
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

void Enemy::SortAbilityPriority()
{
	std::sort(m_abilities.begin(), m_abilities.end(), [](const std::shared_ptr<Ability>& first, const std::shared_ptr<Ability>& second)
		{
			return first->GetCooldown() > second->GetCooldown();
		});
}

int Enemy::RetrunXpDrop()
{
	return m_xpDrop;
}
