#include "Game.h"


bool RunGame(const GameParameters& params)
{
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Guenter", "Otto", "Marcel Davis", "Steve Jobs" };

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);
	std::uniform_int_distribution<int> enemyPositionX(0, params.gridWidth - 1);
	std::uniform_int_distribution<int> enemyPositionY(0, params.gridHeight - 1);
	std::vector<Enemy*> pEnemies;
	std::shared_ptr<Ability> placeholder = std::make_shared<Placeholder>();
	Enemy* pCollidedEnemy;
	bool succesfullCombat;
	int enemyIndex;
	
	Grid playArea(params.gridWidth, params.gridHeight);

	Player player(45, 8, params.playerStart);
	Player* pPlayer = &player;
	pPlayer->SetName(playerNames.at(distribution(gen)));
	pPlayer->FillAbilitiesWithPlaceholders(placeholder);
	pPlayer->LearnAbility(std::make_shared<Fireball>());
	pPlayer->LearnAbility(std::make_shared<Rejuvenate>());


	playArea.SetCharacterAtLocation(pPlayer);


	for (size_t i = 0; i < params.enemyCount; i++)
	{
		int movesAway = 0;
		int2 enemyPosition;
		do
		{
			enemyPosition = int2(enemyPositionX(gen), enemyPositionY(gen));
			if (playArea.GetValueAtLocation(enemyPosition))
				continue;

			movesAway = abs(enemyPosition.x - params.playerStart.x) + abs(enemyPosition.y - params.playerStart.y);
		} while (movesAway < 3);
		
		Enemy* pEnemy = ChooseRandomEnemy(enemyPosition);
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
	if (succesfullCombat)
	{
		playArea.Print();
		std::cout << std::endl;
		std::cout << "All enemies defeated! " << pPlayer->GetName() << " won!" << std::endl;
		std::cout << "Press any button to close the game..." << std::endl;
		_getch();
	}
	return succesfullCombat;
}

Enemy* ChooseRandomEnemy(int2 position)
{
	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());


	int sum_of_weight = 0;
	std::vector<int> choice_weights = { Yeti::m_spawnChance, Crawler::m_spawnChance, Monolith::m_spawnChance, Exile::m_spawnChance, FlameOfFury::m_spawnChance };
	std::vector<char> choices = { 'Y', 'C', 'M', 'E', 'F' };

	for (int i = 0; i < choices.size(); i++) {
		sum_of_weight += choice_weights[i];
	}

	std::uniform_int_distribution<int> distributionOfChoices(0, sum_of_weight);

	int rnd = distributionOfChoices(gen);
	for (int i = 0; i < choices.size(); i++) {
		if (rnd <= choice_weights[i])
		{

			Enemy* enemy;

			switch (choices.at(i))
			{
			case 'Y':
				enemy = new Yeti(position);
				break;
			case 'M':
				enemy = new Monolith(position);
				break;
			case 'C':
				enemy = new Crawler(position);
				break;
			case 'F':
				enemy = new FlameOfFury(position);
				break;
			case 'E':
				enemy = new Exile(position);
				break;
			default:
				enemy = new Enemy();
			}
			return enemy;
		}
		rnd -= choice_weights[i];
	}

}