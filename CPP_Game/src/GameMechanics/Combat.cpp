#include "Combat.h"

bool Combat(Player* player, Enemy* enemy)
{
	int turnNumber = 1;
	player->InitCombat(enemy);
	enemy->InitCombat(player);
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
				if (player->GetAbilityAtIndex(0)->GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(0)->IsReady())
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
				if (player->GetAbilityAtIndex(1)->GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(1)->IsReady())
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
				if (player->GetAbilityAtIndex(2)->GetAbilityName() != "PLACEHOLDER")
				{
					if (player->GetAbilityAtIndex(2)->IsReady())
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

		player->TakeTurn(action);

		if (enemy->Defeated())
		{
			ClearConsole();
			player->m_curXp += enemy->RetrunXpDrop();
			PrintCombat(player, enemy, turnNumber);
			
			std::cout << enemy->GetName() << " was defeated!" << std::endl;

			if (player->LevelUpIsReady())
				player->LevelUp();

			std::cout << "Press any button to continue..." << std::endl;
			player->EndOfCombat();
			_getch();
			return true;
		}


		
		if ((enemy->GetAbilityAtIndex(0)->IsReady()) && enemy->GetAbilityAtIndex(0)->GetAbilityName() != "PLACEHOLDER")
			action = '1';
		else if (enemy->GetAbilityAtIndex(1)->IsReady() && enemy->GetAbilityAtIndex(1)->GetAbilityName() != "PLACEHOLDER")
			action = '2';
		else if (enemy->GetAbilityAtIndex(2)->IsReady() && enemy->GetAbilityAtIndex(2)->GetAbilityName() != "PLACEHOLDER")
			action = '3';
		else
			action = 'a';
		enemy->TakeTurn(action);

		if (player->Defeated())
		{
			ClearConsole();
			PrintCombat(player, enemy, turnNumber);
			std::cout << std::endl;
			std::cout << player->GetName() << " was defeated!" << std::endl;
			std::cout << "Press any button to close the game..." << std::endl;
			_getch();
			return false;
		}

		turnNumber++;
	}

	return true;
}

void PrintCombat(Player* player, Enemy* enemy, int turnNumber)
{
	int currentLine = 3;
	std::cout << player->GetName() << " encountered a wild " << enemy->GetName() << "!" << std::endl;
	std::cout << std::endl;
	currentLine += PrintCombatActions(player, enemy);
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
	std::cout << "Level " << player->GetLevel() << std::endl;
	std::cout << "XP: " << player->m_curXp << "/" << player->GetXpNeeded() <<  std::endl;
	std::cout << "----------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << player->GetLogMsg() << std::endl;
	std::cout << enemy->GetLogMsg() << std::endl;
}

int PrintCombatActions(Player* player, Enemy* enemy)
{
	int row = 1;
	std::cout << "a: Attack: " << std::endl;
	
	if (player->GetAbilityAtIndex(0)->GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "1: " << player->GetAbilityAtIndex(0)->GetAbilityMsg() << std::endl;
		row = 2;
	}
	if (player->GetAbilityAtIndex(1)->GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "2: " << player->GetAbilityAtIndex(1)->GetAbilityMsg() << std::endl;
		row = 3;
	}
	if (player->GetAbilityAtIndex(2)->GetAbilityName() != "PLACEHOLDER")
	{
		std::cout << "3: " << player->GetAbilityAtIndex(2)->GetAbilityMsg() << std::endl;
		row = 4;
	}
	
	return row;
}