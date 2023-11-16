#include "Header/Enemy.h"
#include "Header/Player.h"

Enemy::Enemy()
	:Character()
{}

Enemy::Enemy(int hp, int dmg)
	:Character(hp, dmg)
{}

Enemy::Enemy(int hp, int dmg, int2 position)
	:Character(hp, dmg, position)
{}

void Enemy::AttackPlayer(Player& player)
{
	m_logMsg = "Enemy dealt " + std::to_string(m_dmg) + " damage to Player!";
	player.m_curHp -= m_dmg;
}

int Enemy::TakeTurn(char action)
{
	m_actionFlags = 0;
	switch (action)
	{
	case 'a':
		m_actionFlags |= ATTACKFLAG;
	}
	return m_actionFlags;
}