#include "Game.h"


bool RunGame(const GameParameters& params)
{
	//std::cout << "C++ game by Dominik Mueller (dm126)" << std::endl;
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Günter", "Otto", "Marcel Davis", "Steve Jobs" };
	

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers (here, integers between 1 and 100)
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);
	std::uniform_int_distribution<int> enemyPositionX(0, params.gridWidth - 1);
	std::uniform_int_distribution<int> enemyPositionY(0, params.gridHeight - 1);
	std::vector<Enemy*> pEnemies;
	Enemy* pCollidedEnemy;
	bool succesfullCombat;
	int enemyIndex;
	Ability fireball(3, 10, false, "Fireball");
	Ability heal(3, 12, true, "Heal");
	Ability meteorStrike(4, 15, false, "Meteor Strike");

	Grid playArea(params.gridWidth, params.gridHeight);

	Player player(params.playerHealth, params.playerDamage, params.playerStart);
	Player* pPlayer = &player;
	pPlayer->SetName(playerNames.at(distribution(gen)));

	pPlayer->LearnAbility(fireball);
	pPlayer->LearnAbility(heal);

	playArea.SetCharacterAtLocation(pPlayer);


	for (size_t i = 0; i < params.enemyCount; i++)
	{
		int movesAway = 0;
		int2 enemyPosition;
		bool positionAvailable = true;
		do
		{
			enemyPosition = int2(enemyPositionX(gen), enemyPositionY(gen));
			if (pEnemies.size() > 0)
			{
				for (Enemy* enemy : pEnemies)
				{
					if (enemy->GetPosition() == enemyPosition)
					{
						positionAvailable = false;
						break;
					}
				}
			}
			movesAway = abs(enemyPosition.x - pPlayer->GetPosition().x) + abs(enemyPosition.y - pPlayer->GetPosition().y);
		} while (movesAway <= 3 && positionAvailable);
		
		Enemy* pEnemy = new Enemy(params.enemyHealth, params.enemyDamage, enemyPosition);
		pEnemy->SetName("Visual Studio");
		pEnemy->LearnAbility(meteorStrike);
		pEnemies.push_back(pEnemy);
		playArea.SetCharacterAtLocation(pEnemies.at(i));
	}


	do {
		playArea.Print();
		enemyIndex = NULL;

		pCollidedEnemy = OpenWorld(pPlayer, pEnemies, playArea);

		//Comabt
		succesfullCombat = Combat(pPlayer, pCollidedEnemy);
		if (!succesfullCombat)
		{
			for (Enemy* ptr : pEnemies) {
				delete ptr;
			}
			pEnemies.clear();
			break;
		}
		else
		{
			playArea.SetValueAtLocation(pCollidedEnemy->GetPosition(), false);
			auto enemyToRemove = std::find(pEnemies.begin(), pEnemies.end(), pCollidedEnemy);
			delete *enemyToRemove;
			pEnemies.erase(enemyToRemove);
			playArea.SetCharacterAtLocation(pPlayer);
		}
	} while (pEnemies.size() > 0);
	return succesfullCombat;
}

bool Combat(Player* player, Enemy* enemy)
{
	int turnNumber = 1;
	bool enemyDefeated;

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
			enemyDefeated = true;
			break;
		}


		if ((enemy->GetAbilityAtIndex(0).IsReady()) && enemy->GetAbilityAtIndex(0).GetAbilityName() != "PLACEHOLDER")
			action = '1';
		else if (enemy->GetAbilityAtIndex(1).IsReady() && enemy->GetAbilityAtIndex(1).GetAbilityName() != "PLACEHOLDER")
			action = '2';
		else if (enemy->GetAbilityAtIndex(2).IsReady() && enemy->GetAbilityAtIndex(2).GetAbilityName() != "PLACEHOLDER")
			action = '3';
		else
			action = 'a';
		enemy->TakeTurn(action, player);

		if (player->Defeated())			
			enemyDefeated = false;

		turnNumber++;
	}

	ClearConsole();
	PrintCombat(player, enemy, turnNumber);

	if (enemyDefeated)
	{
		std::cout << enemy->GetName() << " was defeated!" << std::endl;
		player->EndOfCombat();
	}
	else
		std::cout << player->GetName() << " was defeated!" << std::endl;

	std::cout << "Press any button to continue" << std::endl;
	_getch();

	return enemyDefeated;
}

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
				std::cout << input <<" is not a valid move option!" << std::endl;
			}			
			else
				validInput = true;
		} while(!validInput);
		
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

