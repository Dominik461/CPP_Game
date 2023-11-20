#include "Header/Enemy.h"


Enemy::Enemy()
	:Character()
{}

Enemy::Enemy(int hp, int dmg)
	:Character(hp, dmg)
{}

Enemy::Enemy(int hp, int dmg, int2 position)
	:Character(hp, dmg, position)
{
	/*
	MeteorStrike* pMeteorStrike();
	LearnAbility(pMeteorStrike);
	*/
}

void Enemy::AttackPlayer(Character* player)
{
	m_logMsg = "Enemy dealt " + std::to_string(m_dmg) + " damage to Player!";
	player->m_curHp -= m_dmg;
}

void Enemy::TakeTurn(char action, Character* target)
{
	switch (action)
	{
	case 'a':
		AttackPlayer(target);
		break;
	/*
	case '1':
		if(m_pAbilities.at(0) != nullptr)
			m_pAbilities.at(0)->UseAbility(target);
		break;
	case '2':
		if (m_pAbilities.at(1) != nullptr)
			m_pAbilities.at(1)->UseAbility(target);
		break;
	case '3':
		if (m_pAbilities.at(2) != nullptr)
			m_pAbilities.at(2)->UseAbility(target);
		break;
	*/
	}
	ReduceAllCooldowns();
}