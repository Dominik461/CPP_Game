#include "Header/Enemy.h"


Enemy::Enemy()
	:Character()
{}

Enemy::Enemy(int hp, int dmg)
	:Character(hp, dmg)
{}

Enemy::Enemy(int hp, int dmg, int2 position)
	:Character(hp, dmg, position)
{}

void Enemy::AttackPlayer(Character* player)
{
	m_logMsg = "Enemy dealt " + std::to_string(m_dmg) + " damage to " + player->GetName() + "!";
	player->m_curHp -= m_dmg;
}

void Enemy::TakeTurn(char action, Character* target)
{
	switch (action)
	{
	case 'a':
		AttackPlayer(target);
		break;
	case '1':
		m_logMsg = m_abilities.at(0).UseAbility(target, m_name);
		break;
	case '2':
		m_logMsg = m_abilities.at(1).UseAbility(target, m_name);
		break;
	case '3':
		m_logMsg = m_abilities.at(2).UseAbility(target, m_name);
		break;
	}
	ReduceAllCooldowns();
}