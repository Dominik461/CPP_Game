#include "Game.h"


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
	enemy.SetName("Visual Studio");
	playArea.SetCharacterAtLocation(player);
	playArea.SetCharacterAtLocation(enemy);
	playArea.Print();
	

	OpenWorld(playerInputs, params.manual, player, enemy, playArea);

	//Comabt
	return Combat(playerInputs, params.manual ,player, enemy);
}

bool Combat(std::vector<char>& playerInputs, bool manual, Player& player, Enemy& enemy)
{
	int playerActionFlags, enemyActionFlags;
	if ((!manual) && (playerInputs.size() > 0))
	{
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
	}
	else if(manual)
	{
		while (!player.Defeated() && !enemy.Defeated())
		{
			playerActionFlags = 0;
			std::cout << "Use a to attack the enemy or h to heal your self!" << std::endl;
			char action = _getch();
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
	}
	return true;
}

void OpenWorld(std::vector<char>& playerInputs, bool manual ,Player& player, Enemy& enemy, Grid playArea)
{
	if (!manual) {
		while(playerInputs.size() > 0)
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
	else
	{
		while (player.GetPosition() != enemy.GetPosition())
		{
			char input = _getch();

			ClearConsole();
			player.Move(input, playArea);
			if (player.GetPosition() == enemy.GetPosition())
			{
				break;
			}
			playArea.Print();
		}
		ClearConsole();
		std::cout << player.GetName() << " encountered a wild " << enemy.GetName() << "!" << std::endl;
	}
}

void ClearConsole()
{
	system("cls");
}