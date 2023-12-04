#include "Header/Grid.h"


Grid::Grid(unsigned int width, unsigned int height)
	:m_Height(height), m_Width(width)
{
	InitializeCells();
}

void Grid::InitializeCells()
{
	int index;
	for (size_t y = 0; y < m_Height; y++)
	{
		for (size_t x = 0; x < m_Width; x++)
		{
			m_Values.push_back(Cell::Cell(int2::int2(x, y)));
			index = m_Width * y + x;
			SetValueAtIndex(index, false);
		}
	}
}

bool Grid::GetValueAtIndex(unsigned int index)
{
	if (IndexInBounds(index))
		return m_Values.at(index).blocked;
}

bool Grid::GetValueAtLocation(int2 location)
{
	if (LocationInBounds(location))
		return  m_Values.at(GetIndexFromLocation(location)).blocked;
		
}

void Grid::SetValueAtIndex(unsigned int index, bool value)
{
	if (IndexInBounds(index))
		m_Values.at(index).blocked = value;	
}

void Grid::SetValueAtLocation(int2 location, bool value)
{
	if (LocationInBounds(location))
	{
		m_Values.at(GetIndexFromLocation(location)).blocked = value;
		if(!value)
			m_Values.at(GetIndexFromLocation(location)).ClearCharacterPointer();
	}
}

void Grid::SetCharacterAtLocation(Character* character)
{
	if (LocationInBounds(character->GetPosition()))
	{
		m_Values.at(GetIndexFromLocation(character->GetPosition())).blocked = true;
		m_Values.at(GetIndexFromLocation(character->GetPosition())).SetCharacterPosition(character);
	}
}


Character* Grid::GetCharacterAtLocation(int2 pos)
{
	if (LocationInBounds(pos))
		return m_Values.at(GetIndexFromLocation(pos)).GetCharacter();
	
	return NULL;
}

unsigned int Grid::GetIndexFromLocation(int2 location)
{
	if (LocationInBounds(location))
		return m_Width * location.y + location.x;
}

int2 Grid::GetLocationFromIndex(unsigned int index)
{
	if (IndexInBounds(index))
		return int2(index % m_Width, index / m_Width);
}

unsigned int Grid::GetWidth()
{
	return m_Width;
}

unsigned int Grid::GetHeight()
{
	return m_Height;
}

bool Grid::IndexInBounds(unsigned int index)
{
	if (index < m_Width * m_Height)
		return true;
		
	std::cout << "This index (" << index << ") is out of bounds" << std::endl;
	return false;
}

bool Grid::LocationInBounds(int2 location)
{
	if (((location.x < m_Width) && (location.y < m_Height)) && ((location.x >= 0) && (location.y >= 0)))
		return true;

	return false;
}

void Grid::Print()
{
	system("cls");
	std::cout << "C++ game by Dominik Mueller(dm126)" << std::endl;
	for (int y = m_Height - 1; y >= 0; --y)
	{
		for (size_t x = 0; x < m_Width; ++x)
		{
			int2 currentLocation(x, y);
			bool value = GetValueAtLocation(currentLocation);
			Character* occupant = m_Values.at(GetIndexFromLocation(currentLocation)).GetCharacter();

			if (value == 0 && occupant == NULL) {
				std::cout << "." << " ";
			}
			else if (value == 1 && occupant != NULL) {
				std::cout << occupant->GetSymbol() << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << "Move with w, a, s ,d!" << std::endl;
}
