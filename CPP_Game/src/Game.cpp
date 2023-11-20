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
	Enemy* pEnemy = &enemy;
	Player* pPlayer = &player;
	pPlayer->SetName(playerNames.at(distribution(gen)));
	pEnemy->SetName("Visual Studio");
	playArea.SetCharacterAtLocation(pPlayer);
	playArea.SetCharacterAtLocation(pEnemy);
	playArea.Print();
	

	OpenWorld(playerInputs, pPlayer, pEnemy, playArea);

	//Comabt
	return Combat(playerInputs, pPlayer, pEnemy);
}

bool Combat(std::vector<char>& playerInputs, Player* player, Enemy* enemy)
{
	const std::vector<char> validInputs = { 'a', '1', '2' };
	int turnNumber = 0;
	while (!player->Defeated() && !enemy->Defeated())
	{
		char action;
		bool vaildInput = false;
		ClearConsole();
		PrintCombat(player, enemy, turnNumber);
		do
		{
			action = _getch();
			auto it = std::find(validInputs.begin(), validInputs.end(), action);
			vaildInput = (it != validInputs.end());
			if (!vaildInput)
				std::cout << "Not a valid input!" << std::endl;
		} while (!vaildInput);
			
			
 		player->TakeTurn(action, enemy);

		if (enemy->Defeated())
		{
			std::cout << enemy->GetName() << " was defeated!" << std::endl;
			return true;
		}

		enemy->TakeTurn('a', player);

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
	std::cout << player->GetName() << " encountered a wild " << enemy->GetName() << "!" << std::endl;
	std::cout <<  std::endl;
	std::cout << "Use 'a' to attack the enemy or 'h' to heal your self!" << std::endl;
	std::cout << "Turn: " << turnNumber << std::endl;
	std::cout << std::endl;

	std::cout << "  o";
	moveTo(42, 6);
	std::cout << "o  " << std::endl;
	std::cout << " /|\\";
	moveTo(41, 7);
	std::cout << "/|\\  " << std::endl;
	std::cout << "  |  ";
	moveTo(42, 8);
	std::cout << "|  " << std::endl;
	std::cout << " / \\";
	moveTo(41, 9);
	std::cout << "/ \\  " << std::endl;
	std::cout << player->GetName();
	moveTo(40, 10);
	std::cout << enemy->GetName() << std::endl;
	std::cout << player->m_curHp << "/" << player->GetMaxHP();
	moveTo(40, 11);
	std::cout << enemy->m_curHp << "/" << enemy->GetMaxHP() << std::endl;
	//std::cout << player.GetLogMsg() << std::endl;
	//std::cout << enemy.GetLogMsg() << std::endl;
}

void ClearConsole()
{
	system("cls");
}

void moveTo(int x, int y) 
{
	std::cout << "\033[" << y << ";" << x << "H";
}