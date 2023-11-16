#include "Game.h"
#include <iostream>

bool RunGame(const GameParameters& params)
{
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Günter", "Otto", "Marcel Davis", "Steve Jobs" };
	std::vector<char> playerInputs = params.playerInputs;

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers (here, integers between 1 and 100)
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);


	Grid playArea(params.gridWidth, params.gridHeight);
	Enemy enemy(params.enemyHealth, params.enemyDamage, params.enemyPosition);
	Player player(params.playerHealth, params.playerDamage, params.playerHeal, params.playerStart);
	player.SetName(playerNames.at(distribution(gen)));
	enemy.SetName("Goblin");
	playArea.SetCharacterAtLocation(player);
	playArea.SetCharacterAtLocation(enemy);
	playArea.Print();
	

	OpenWorld(playerInputs, params.manual, player, enemy, playArea);

	//Comabt
	return Combat(playerInputs, params.manual ,player, enemy);
}

bool Combat(std::vector<char>& playerInputs, bool manual, Player& player, Enemy& enemy)
{
	if (!manual)
	{
		int playerActionFlags, enemyActionFlags;
		for (char action : playerInputs)
		{
			playerActionFlags = 0;
			playerActionFlags = player.TakeTurn(action);
			if (playerActionFlags & ATTACKFLAG)
			{
				player.AttackEnemy(enemy);
				if (enemy.Defeated())
				{
					std::cout << enemy.GetName() << " was defeated!" << std::endl;
					return true;
				}
			}
			else if (playerActionFlags & HEALFLAG)
			{
				player.HealSelf();
			}

			enemyActionFlags = 0;
			enemyActionFlags = enemy.TakeTurn('a');
			if (enemyActionFlags & ATTACKFLAG)
			{
				enemy.AttackPlayer(player);
				if (player.Defeated())
				{
					std::cout << player.GetName() << " was defeated!" << std::endl;
					return false;
				}
			}

		}
		return true;
	}
	//TO DO MANUAL MODE IMPLEMENT
	return false;
}

void OpenWorld(std::vector<char>& playerInputs, bool manual ,Player& player, Enemy& enemy, Grid playArea)
{
	if (!manual) {
		for (size_t i = 0; i < playerInputs.size(); i++)
		{
			char input = playerInputs.at(0);
			playerInputs.erase(playerInputs.begin());

			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			std::cout << std::endl;
			player.Move(input, playArea);

			if (player.GetPosition() == enemy.GetPosition())
			{	
				ClearConsole();
				std::cout << player.GetName() << " encountered a wild " << enemy.GetName() << "!" << std::endl;
				break;
			}

			playArea.Print();
		}
	}

}

void ClearConsole()
{
	system("cls");
}