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
	m_symbole = 'e';
}