#pragma once
#include "Character.h"
#include "Player.h"
#include "../../GameMechanics/Element.h"
#include "../../Abilities/Header/AllAbilites.h"
#include <algorithm>

class Player;

class Enemy : public Character
{
protected:
	int m_xpDrop;
	Element m_element;

public:	
	Enemy();
	Enemy(int hp, int dmg, char symbole, std::string name, int2 position, Element element);
	Enemy(int hp, int dmg, int2 position);
	void InitCombat(Character* pTarget) override;
	void SortAbilityPriority();
	int RetrunXpDrop();

};