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

	
	//Open World
	playArea.SetValueAtLocation(player);
	playArea.SetValueAtLocation(enemy);
	playArea.Print();

	//Comabt
	return Combat(params, player, enemy);
}

bool Combat(const GameParameters& params, Player& player, Enemy& enemy)
{
	int playerActionFlags, enemyActionFlags;
	for (char action : params.playerInputs)
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