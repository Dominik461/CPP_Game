#include "ConsoleHelpers.h"

void moveTo(int x, int y)
{
	std::cout << "\033[" << y << ";" << x << "H";
}

void ClearConsole()
{
	system("cls");
}