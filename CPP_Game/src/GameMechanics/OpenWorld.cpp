#include "OpenWorld.h"


Enemy* OpenWorld(Player* player, std::vector<Enemy*> enemies, Grid& playArea)
{
	char input;
	bool validInput = false;
	while (true)
	{
		do {
			input = _getch();
			if (input != 'w' && input != 'a' && input != 's' && input != 'd')
			{
				validInput = false;
				std::cout << input << " is not a valid move option!" << std::endl;
			}
			else
				validInput = true;
		} while (!validInput);

		player->Move(input, playArea);
		for (Enemy* enemy : enemies)
		{

			if (player->GetPosition() == enemy->GetPosition())
			{
				ClearConsole();
				return enemy;
			}
		}
		playArea.Print();
		std::cout << player->GetLogMsg() << std::endl;
	}

}