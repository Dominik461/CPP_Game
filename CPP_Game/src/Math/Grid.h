#pragma once
#include <iostream>
#include <vector>
#include "Cell.h"
#include "Int2.h"
#include "../Character/Header/Enemy.h"
#include "../Character/Header/Player.h"

class Grid
{
public:
	Grid(unsigned int width, unsigned int height); //initialize m_Width and m_Height and call InitializeCells()

	void InitializeCells(); //set all cells to be not blocked and initialize their positions
	bool GetValueAtIndex(unsigned int index); //retrieve whether or not a cell at a given index is blocked
	bool GetValueAtLocation(int2 location); //retrieve whether or not a cell at a given location is blocked
	void SetValueAtIndex(unsigned int index, bool value); //set the blocked value of a cell at a given index
	void SetValueAtLocation(int2 location, bool value); //set the blocked value of a given location
	void SetCharacterAtLocation(Character* character); //set the blocked value of a given location
	Character* GetCharacterAtLocation(int2 pos); //set the blocked value of a given location
	unsigned int GetIndexFromLocation(int2 location); //convert a location to an index
	int2 GetLocationFromIndex(unsigned int index); //convert an index into a location
	unsigned int GetWidth(); //retrieve the width of the grid
	unsigned int GetHeight(); //retrieve the height of the grid
	bool IndexInBounds(unsigned int index); //check, whether a given index is in the bounds of the grid
	bool LocationInBounds(int2 location); //check, whether a given location is in the bounds of the grid

	/*
	Print the grid in the following format (1 for blocked, 0 for free):
	Grid:
	0 0 0 0 0
	0 1 0 0 0
	0 1 1 1 1
	*/
	void Print();
private:
	unsigned int m_Width;
	unsigned int m_Height;

	std::vector<Cell> m_Values;

};