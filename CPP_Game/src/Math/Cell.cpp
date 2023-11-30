#include "Math/Cell.h"

Cell::Cell(int2 position)
	: m_Position(position), m_pCharacter(NULL)
{}

int2 Cell::GetPosition()
{
	return m_Position;
}

void Cell::SetCharacterPosition(Character* character)
{
	if (m_pCharacter == NULL)
		m_pCharacter = character;
	else
		m_pCharacter = NULL;
}

void Cell::ClearCharacterPointer()
{
	m_pCharacter = NULL;
}

Character* Cell::GetCharacter()
{
	return m_pCharacter;
}