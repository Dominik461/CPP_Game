#include "Game.h"


bool RunGame(const GameParameters& params)
{
	std::cout << "C++ game by Dominik Mueller (dm126)" << std::endl;
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Günter", "Otto", "Marcel Davis", "Steve Jobs" };
	std::vector<char> playerInputs = params.playerInputs;

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers (here, integers between 1 and 100)
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);

	Ability fireball(3, 10, false, "Fireball");
	Ability heal(3, 12, true, "Heal");
	Ability meteorStrike(4, 15, false, "Meteor Strike");

	Grid playArea(params.gridWidth, params.gridHeight);
	Enemy enemy(params.enemyHealth, params.enemyDamage, params.enemyPosition);
	Player player(params.playerHealth, params.playerDamage, params.playerHeal, params.playerStart);
	Enemy* pEnemy = &enemy;
	Player* pPlayer = &player;
	pPlayer->SetName(playerNames.at(distribution(gen)));
	pEnemy->SetName("Visual Studio");
	pPlayer->LearnAbility(fireball);
	pPlayer->LearnAbility(heal);
	pEnemy->LearnAbility(meteorStrike);

	playArea.SetCharacterAtLocation(pPlayer);
	playArea.SetCharacterAtLocation(pEnemy);
	playArea.Print();
	

	OpenWorld(playerInputs, pPlayer, pEnemy, playArea);

	//Comabt
	return Combat(playerInputs, pPlayer, pEnemy);
}

bool Combat(std::vector<char>& playerInputs, Player* player, Enemy* enemy)
{
	int turnNumber = 1;

	while (!player->Defeated() && !enemy->Defeated())
	{
		char action;
		bool validInput = false;
		ClearConsole();
		PrintCombat(player, enemy, turnNumber);
		do
		{
			action = _getch();
			switch (action)
			{
			case 'a':
				validInput = true;
				break;
			case '1':
				if (player->GetAbilityAtIndex(0).GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(0).IsReady())
						validInput = true;
					else
					{
						std::cout << "1st ability not ready" << std::endl;
						validInput = false;
					}
				}
				else
				{
					std::cout << "1st ability not learned" << std::endl;
					validInput = false;
				}
				break;

			case '2':
				if (player->GetAbilityAtIndex(1).GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(1).IsReady())
						validInput = true;
					else
					{
						std::cout << "2nd ability not ready" << std::endl;
						validInput = false;
					}
				}
				else
				{
					std::cout << "2nd ability not learned" << std::endl;
					validInput = false;
				}
				break;

			case '3':
				if (player->GetAbilityAtIndex(2).GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(2).IsReady())
						validInput = true;
					else
					{
						std::cout << "3rd ability not ready" << std::endl;
						validInput = false;
					}
				}
				else
				{
					std::cout << "3rd ability not learned" << std::endl;
					validInput = false;
				}
				break;

			default:
				std::cout << "Not a valid input!" << std::endl;
				break;
			}
		} while (!validInput);	

 		player->TakeTurn(action, enemy);

		if (enemy->Defeated())
		{
			std::cout << enemy->GetName() << " was defeated!" << std::endl;
			return true;
		}

		if (enemy->GetAbilityAtIndex(0).IsReady())
			action = '1';
		else if (enemy->GetAbilityAtIndex(1).IsReady())
			action = '2';
		else if (enemy->GetAbilityAtIndex(2).IsReady())
			action = '3';
		else
			action = 'a';
		enemy->TakeTurn(action, player);

		if (player->Defeated())
		{
			std::cout << player->GetName() << " was defeated!" << std::endl;
			return false;
		}

		turnNumber++;
	}

	return true;
}

void OpenWorld(std::vector<char>& playerInputs, Player* player, Enemy* enemy, Grid playArea)
{
	while (player->GetPosition() != enemy->GetPosition())
	{
		char input = _getch();

		ClearConsole();
		player->Move(input, playArea);
		if (player->GetPosition() == enemy->GetPosition())
		{
			break;
		}
		playArea.Print();
	}
	ClearConsole();		
}

void PrintCombat(Player* player, Enemy* enemy, int turnNumber)
{
	int currentLine = 3;
	std::cout << player->GetName() << " encountered a wild " << enemy->GetName() << "!" << std::endl;
	std::cout <<  std::endl;
	currentLine  += PrintCombatActions(player, enemy);
	std::cout << "Turn: " << turnNumber << std::endl;
	currentLine++;
	std::cout << std::endl;
	currentLine++;
 	std::cout << "  o";
	moveTo(42, currentLine++);
	std::cout << "o  " << std::endl;
	std::cout << " /|\\";
	moveTo(41, currentLine++);
	std::cout << "/|\\  " << std::endl;
	std::cout << "  |  ";
	moveTo(42, currentLine++);
	std::cout << "|  " << std::endl;
	std::cout << " / \\";
	moveTo(41, currentLine++);
	std::cout << "/ \\  " << std::endl;
	std::cout << player->GetName();
	moveTo(40, currentLine++);
	std::cout << enemy->GetName() << std::endl;
	std::cout << player->m_curHp << "/" << player->GetMaxHP();
	moveTo(40, currentLine++);
	std::cout << enemy->m_curHp << "/" << enemy->GetMaxHP() << std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << player->GetLogMsg() << std::endl;
	std::cout << enemy->GetLogMsg() << std::endl;
}

int PrintCombatActions(Player* player, Enemy* enemy)
{
	int row = 1;
	std::cout << "a: Attack: " << std::endl;
	if (player->GetAbilityAtIndex(0).GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "1: " << player->GetAbilityAtIndex(0).GetAbilityMsg() << std::endl;
		row = 2;
	}
	if (player->GetAbilityAtIndex(1).GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "2: " << player->GetAbilityAtIndex(1).GetAbilityMsg() << std::endl;
		row = 3;
	}
	if (player->GetAbilityAtIndex(2).GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "3: " << player->GetAbilityAtIndex(2).GetAbilityMsg() << std::endl;
		row = 4;
	}
	return row;
}

void ClearConsole()
{
	system("cls");
}

void moveTo(int x, int y) 
{
	std::cout << "\033[" << y << ";" << x << "H";
}

