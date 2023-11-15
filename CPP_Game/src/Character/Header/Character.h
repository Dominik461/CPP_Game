#pragma once
#define ATTACKFLAG 0x01
#define HEALFLAG 0x02
#include "../../Math/Int2.h"
#include <iostream>

class Character
{
	protected:
		int m_dmg, m_maxHp, m_actionFlags;
		int2 m_position;
		std::string m_name = "";

	public:
		int m_curHp;
		Character();
		Character(int hp, int dmg);
		Character(int hp, int dmg, int2 position);
		void SetName(std::string name);
		std::string GetName();
		virtual int TakeTurn(char action) = 0;
		int2 GetPosition();
		bool Defeated();
};