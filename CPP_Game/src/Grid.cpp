#include "Math/Grid.h"
#include <iostream>

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

void Grid::SetValueAtLocation(Character& character)
{
	if (LocationInBounds(character.GetPosition()))
	{
		m_Values.at(GetIndexFromLocation(character.GetPosition())).blocked = true;
		m_Values.at(GetIndexFromLocation(character.GetPosition())).SetCharacterPosition(character);
	}
}

unsigned int Grid::GetIndexFromLocation(int2 location)
{
	if (LocationInBounds(location))
		return m_Width * location.y + location.x;;
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
	if (location.x <= m_Width && location.y <= m_Height)
		return true;
		
	std::cout << "This location (" << location.x << "|" << location.y << ") is out of bounds" << std::endl;
	return false;
}

void Grid::Print()
{
	std::cout << "Grid:" << std::endl;
	for (size_t y = 0; y < m_Height; y++)
	{
		for (size_t x = 0; x < m_Width; x++)
		{
			int2 currentLocation(x, y);
			bool value = GetValueAtLocation(currentLocation);
			Character* occupant = m_Values.at(GetIndexFromLocation(currentLocation)).GetCharacter();


			if (value == 0 && occupant == NULL) {
				std::cout << "." << " ";
			}
			else if (typeid(*occupant) == typeid(Player)) {
				std::cout << "p" << " ";
			}
			else if (typeid(*occupant) == typeid(Enemy)) {
				std::cout << "e" << " ";
			}
		}
		std::cout << std::endl;
	}
}
