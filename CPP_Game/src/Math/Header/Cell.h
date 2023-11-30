#pragma once
#include "Int2.h"
#include "../../Character/Header/Character.h"

class Cell
{
private:
	int2 m_Position;
	Character* m_pCharacter;

public:
	Cell(int2 position);

	int2 GetPosition();
	Character* GetCharacter();
	void SetCharacterPosition(Character* character);
	void ClearCharacterPointer();
	bool blocked = false;
}; 