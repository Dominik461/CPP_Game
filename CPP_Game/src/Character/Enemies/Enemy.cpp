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