#include "Game.h"


bool RunGame(const GameParameters& params)
{
	//init gameworld
	std::vector<std::string> playerNames = { "Olaf", "Gaben", "Günter", "Otto", "Marcel Davis", "Steve Jobs" };

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());

	// Define a distribution for the random numbers
	std::uniform_int_distribution<int> distribution(0, playerNames.size() - 1);
	std::uniform_int_distribution<int> enemyPositionX(0, params.gridWidth - 1);
	std::uniform_int_distribution<int> enemyPositionY(0, params.gridHeight - 1);
	std::vector<Enemy*> pEnemies;
	Enemy* pCollidedEnemy;
	bool succesfullCombat;
	int enemyIndex;
	
	Fireball fireball(3, 10, "Fireball");
	/*
	Ability fireball(3, 10, false, "Fireball");
	Ability heal(3, 12, true, "Heal");
	Ability meteorStrike(4, 15, false, "Meteor Strike");
	*/
	Grid playArea(params.gridWidth, params.gridHeight);

	Player player(params.playerHealth, params.playerDamage, params.playerStart);
	Player* pPlayer = &player;
	pPlayer->SetName(playerNames.at(distribution(gen)));

	//pPlayer->LearnAbility(fireball);
	//pPlayer->LearnAbility(heal);

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
		//pEnemy->LearnAbility(meteorStrike);
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