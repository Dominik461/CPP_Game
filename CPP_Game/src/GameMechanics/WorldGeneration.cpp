#include "WorldGeneration.h".

WorldGeneration::WorldGeneration(bool debug)
	: mInputFile("resources/World.txt"), mDebug(debug)
{}

std::shared_ptr<World> WorldGeneration::GenerateWorld()
{
    if (std::getline(mInputFile, mLine))
	{
        // Find the position of the stop characters ('-')
        size_t pos = mLine.find('-');

        // Extract the part before the stop characters (or the entire line if not found)
        mPlayerSpawnRegion = mLine.substr(0, pos);

        // Extract the part after the stop characters (if found)
        std::string playerSpawnLocationString = (pos != std::string::npos) ? mLine.substr(pos + 1) : "";
        pos = playerSpawnLocationString.find(',');
        mPlayerSpawnLocation = int2(std::stoi(playerSpawnLocationString.substr(0, pos)), std::stoi((pos != std::string::npos) ? playerSpawnLocationString.substr(pos + 1) : ""));


        // Print both parts
		PrintIfDebug("Player spawn region: " + mPlayerSpawnRegion);
		//too lazy to add the operator for int2 class
		if(mDebug)
			std::cout << "Player spawn location: " << mPlayerSpawnLocation << std::endl;
		
    }

	mWorld = std::make_shared<World>(mPlayerSpawnRegion, mPlayerSpawnLocation);

    GenerateRegion();

	mInputFile.close();
	if (mDebug) 
	{
		mWorld->DebugPrintAllRegions();
		std::cin >> mLine;
	}		

	return mWorld;
}

void WorldGeneration::GenerateRegion()
{
	mCounter++;
	//some random bug where when I use the function the call gets eat letter by letter but only this string
	if(mDebug)
		std::cout << "Call of function: " << mCounter << "\n";

	if (!mInputFile.eof())
	{
		int x = 16, y = 16, chunkCounter = 0;
		bool newChunk = true;
		bool newRegion = true;

		std::getline(mInputFile, mLine);
		std::string regionName = mLine;
		std::getline(mInputFile, mLine);
		std::string regionSymbole = mLine;
		std::getline(mInputFile, mLine);

		int difficultyScale = std::stoi(mLine);
		std::getline(mInputFile, mLine);
		std::string spawnChances = mLine;

		PrintIfDebug("Region name: " + regionName);
		PrintIfDebug("Region spawn chances: " + spawnChances);


		std::shared_ptr<Region> region = std::make_shared<Region>(regionName, regionSymbole);

		#pragma region ReadEnemySpawnChances
		size_t pos = 2;

		for (size_t i = 0; i < 5; i++)
		{
			// Extract the part before the stop characters (or the entire line if not found)
			std::string spawnChance = spawnChances.substr(0, pos);
			PrintIfDebug(spawnChance);

			std::string enemyType = spawnChances.substr(0, 1);
			PrintIfDebug(enemyType);
			region->AddEnemyTypeToChoice(enemyType[0]);

			int chance = std::stoi((1 != std::string::npos) ? spawnChance.substr(1) : "");
			PrintIfDebug(std::to_string(chance));
			region->AddChoiceWeight(chance);

			spawnChances = (pos != std::string::npos) ? spawnChances.substr(pos) : "";
			PrintIfDebug(spawnChances);
		}
		#pragma endregion
		
		int currentLine = 0;
		while (std::getline(mInputFile, mLine))
		{
			
			PrintIfDebug("Line that gets proccessed: " + mLine);
			if (newChunk)
			{
				newChunk = false;
				currentLine = 0;
				mGrid = std::make_shared<Grid>(x, y);
				mChunk = std::make_shared<Chunk>();
			}

			if (mLine != "-")
			{
				if (mLine[0] == '@' || mLine[0] == '.')
				{
					for (size_t i = 0; i < mLine.length(); i++)
					{
						
						if (mLine[i] == '@')
							mGrid->SetValueAtLocation(int2(i, y - 1 - currentLine), true);
						else if (mLine[i] == '.')
							mGrid->SetValueAtLocation(int2(i, y - 1 - currentLine), false);

						if (mDebug)
							std::cout << "Current char processed: " << mLine[i] << " Value that was set: " << mGrid->GetValueAtLocation(int2(i, y - 1 - currentLine)) << std::endl;

 					}
				}
				else
				{
					GenerateEnemiesForChunk(x, y, difficultyScale, region, regionSymbole+std::to_string(chunkCounter));
					mChunk->SetGrid(mGrid);
					for (int i = 0; i < 4; i++)
					{						
						// Find the position of the stop characters ('-')
						size_t pos = mLine.find(',');

						// Extract the part before the stop characters (or the entire line if not found)
						std::string nextRegion = mLine.substr(0, pos);

						switch (i)
						{
						case 0:
							mChunk->mNextRegionN = nextRegion;
							break;
						case 1:
							mChunk->mNextRegionE = nextRegion;
							break;
						case 2:
							mChunk->mNextRegionS = nextRegion;
							break;
						case 3:
							mChunk->mNextRegionW = nextRegion;
							break;
						}

						// Extract the part after the stop characters (if found)
						mLine = (pos != std::string::npos) ? mLine.substr(pos + 1) : "";
					}
					PrintIfDebug("Chunk with enemies:");
					if(mDebug)
						mChunk->DebugPrintGrid();
					region->AddChunk(mChunk);
					chunkCounter++;
					newChunk = true;
				}
			}
			else if (mLine == "-")
			{
				mWorld->AddRegion(region);
				PrintIfDebug("New Region");

				GenerateRegion();
			}			
			
			if (mInputFile.eof() != 0 && !mEndOfTextfile)
			{
				mWorld->AddRegion(region);
				PrintIfDebug("End of file");
				mEndOfTextfile = true;
				return;
			}				

			currentLine++;
		}
	}
}

void WorldGeneration::PrintIfDebug(std::string line)
{
	if (mDebug)
		std::cout << line << "\n";
}

void WorldGeneration::PrintIfDebug(bool line)
{
	if (mDebug)
		std::cout << line << "\n";
}


void WorldGeneration::GenerateEnemiesForChunk(int x, int y, int difficultyScale, std::shared_ptr<Region> region, std::string currentRegionChunk)
{
	PrintIfDebug("Chunk to generateEnemies: " + currentRegionChunk);
	int enemyNumber;
	int2 position;

	std::uniform_int_distribution<int> enemyPositionX(1, x - 2);
	std::uniform_int_distribution<int> enemyPositionY(1, y - 2);
	std::uniform_int_distribution<int> enemyCount(3, 6);

	// Seed for the random number generator
	std::random_device rd;
	// Mersenne Twister random number generator
	std::mt19937 gen(rd());
	enemyNumber = enemyCount(gen);
	PrintIfDebug("Number of enemies for this chunk: " + std::to_string(enemyNumber));

	for (size_t i = 0; i < enemyNumber; i++)
	{
		int movesAway = 0;
		do
		{
			position = int2(enemyPositionX(gen), enemyPositionY(gen));

			if (mDebug)
				std::cout << "Enemy spawn position: " << position << " Blocked: " << mGrid->GetValueAtLocation(position) << std::endl;

			if (currentRegionChunk == mPlayerSpawnRegion)
			{
				if (mGrid->GetValueAtLocation(position) || position == mPlayerSpawnLocation)
					continue;
				else
					movesAway = abs(position.x - mPlayerSpawnLocation.x) + abs(position.y - mPlayerSpawnLocation.y);
			}				
			else
			{
				if (mGrid->GetValueAtLocation(position))
					continue;
				else
					movesAway = 4;
			}
				
		} while (movesAway < 3);

		int sum_of_weights = 0;
		for (int i = 0; i < region->GetEnemyTypeChoices().size(); i++) {
			sum_of_weights += region->GetChoiceWeightAtIndex(i);
		}

		//the -1 is needed because the generated number should be 1 lower than sum_of_weights and in this function both arugments are inclusive
		std::uniform_int_distribution<int> distributionOfChoices(0, sum_of_weights - 1);

		int rnd = distributionOfChoices(gen);
		
		PrintIfDebug("Sum of weights: " + std::to_string(sum_of_weights));
		PrintIfDebug("Random number from sum of weights: " + std::to_string(rnd));

		for (int i = 0; i < region->GetEnemyTypeChoices().size(); i++) {
			if (rnd < region->GetChoiceWeightAtIndex(i))
			{
				PrintIfDebug("Choosen enemy: " + region->GetEnemyTypeChoiceAtIndex(i));
				Enemy* enemy;
				switch (region->GetEnemyTypeChoiceAtIndex(i))
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
					std::cout << "I should never land here\n";
					enemy = new Enemy();
				}
				PrintIfDebug("New enemy added: " + enemy->GetName());
				mChunk->AddEnemy(enemy);
				break;
			}
			rnd -= region->GetChoiceWeightAtIndex(i);
		}

		PrintIfDebug(std::to_string(mChunk->GetEnemyVector().size()));
		PrintIfDebug(mChunk->GetEnemyAtIndex(i)->GetName());
		
		mGrid->SetCharacterAtLocation(mChunk->GetEnemyAtIndex(i));		
	}
}

