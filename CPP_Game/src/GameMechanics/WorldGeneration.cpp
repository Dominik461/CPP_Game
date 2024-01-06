#include "WorldGeneration.h".

WorldGeneration::WorldGeneration(bool debug)
	: m_inputFile("resources/World.txt"), m_debug(debug)
{}

std::shared_ptr<World> WorldGeneration::GenerateWorld()
{
    if (std::getline(m_inputFile, m_line))
	{
        // Find the position of the stop characters ('-')
        size_t pos = m_line.find('-');

        // Extract the part before the stop characters (or the entire line if not found)
        m_playerSpawnRegion = m_line.substr(0, pos);

        // Extract the part after the stop characters (if found)
        std::string playerSpawnLocationString = (pos != std::string::npos) ? m_line.substr(pos + 1) : "";
        pos = playerSpawnLocationString.find(',');
        m_playerSpawnLocation = int2(std::stoi(playerSpawnLocationString.substr(0, pos)), std::stoi((pos != std::string::npos) ? playerSpawnLocationString.substr(pos + 1) : ""));


        // Print both parts
		PrintIfDebug("Player spawn region: " + m_playerSpawnRegion);
		//too lazy to add the operator for int2 class
		if(m_debug)
			std::cout << "Player spawn location: " << m_playerSpawnLocation << std::endl;
		
    }

	m_world = std::make_shared<World>(m_playerSpawnRegion, m_playerSpawnLocation);

    GenerateRegion();

	m_inputFile.close();
	if (m_debug) 
	{
		m_world->DebugPrintAllRegions();
		std::cin >> m_line;
	}		

	return m_world;
}

void WorldGeneration::GenerateRegion()
{
	m_counter++;
	//some random bug where when I use the function the call gets eat letter by letter but only this string
	if(m_debug)
		std::cout << "Call of function: " << m_counter << "\n";

	if (!m_inputFile.eof())
	{
		int x = 16, y = 16, chunkCounter = 0;
		bool newChunk = true;
		bool newRegion = true;

		std::getline(m_inputFile, m_line);
		std::string regionName = m_line;
		std::getline(m_inputFile, m_line);
		std::string regionSymbole = m_line;
		std::getline(m_inputFile, m_line);

		double difficultyScale = std::stod(m_line);

		std::getline(m_inputFile, m_line);
		std::string spawnChances = m_line;

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
		while (std::getline(m_inputFile, m_line))
		{
			
			PrintIfDebug("Line that gets proccessed: " + m_line);
			if (newChunk)
			{
				newChunk = false;
				currentLine = 0;
				m_grid = std::make_shared<Grid>(x, y);
				m_chunk = std::make_shared<Chunk>();
			}

			if (m_line != "-")
			{
				if (m_line[0] == '@' || m_line[0] == '.')
				{
					for (size_t i = 0; i < m_line.length(); i++)
					{
						
						if (m_line[i] == '@')
							m_grid->SetValueAtLocation(int2(i, y - 1 - currentLine), true);
						else if (m_line[i] == '.')
							m_grid->SetValueAtLocation(int2(i, y - 1 - currentLine), false);

						if (m_debug)
							std::cout << "Current char processed: " << m_line[i] << " Value that was set: " << m_grid->GetValueAtLocation(int2(i, y - 1 - currentLine)) << std::endl;

 					}
				}
				else
				{
					GenerateEnemiesForChunk(x, y, difficultyScale, region, regionSymbole+std::to_string(chunkCounter));
					m_chunk->SetGrid(m_grid);
					for (int i = 0; i < 4; i++)
					{						
						// Find the position of the stop characters ('-')
						size_t pos = m_line.find(',');

						// Extract the part before the stop characters (or the entire line if not found)
						std::shared_ptr<std::string> nextRegion = std::make_shared<std::string>(m_line.substr(0, pos));
						m_chunk->mp_nextChunk.push_back(nextRegion);

						// Extract the part after the stop characters (if found)
						m_line = (pos != std::string::npos) ? m_line.substr(pos + 1) : "";
					}
					PrintIfDebug("Chunk with enemies:");
					if(m_debug)
						m_chunk->DebugPrintGrid();
					region->AddChunk(m_chunk);
					chunkCounter++;
					newChunk = true;
				}
			}
			else if (m_line == "-")
			{
				m_world->AddRegion(region);
				PrintIfDebug("New Region");

				GenerateRegion();
			}			
			
			if (m_inputFile.eof() != 0 && !m_endOfTextfile)
			{
				m_world->AddRegion(region);
				PrintIfDebug("End of file");
				m_endOfTextfile = true;
				return;
			}				

			currentLine++;
		}
	}
}

void WorldGeneration::PrintIfDebug(std::string line)
{
	if (m_debug)
		std::cout << line << "\n";
}

void WorldGeneration::PrintIfDebug(bool line)
{
	if (m_debug)
		std::cout << line << "\n";
}


void WorldGeneration::GenerateEnemiesForChunk(int x, int y, double difficultyScale, std::shared_ptr<Region> region, std::string currentRegionChunk)
{
	PrintIfDebug("Chunk to generateEnemies: " + currentRegionChunk);
	int enemyNumber;
	int2 position;

	std::uniform_int_distribution<int> enemyPositionX(1, x - 2);
	std::uniform_int_distribution<int> enemyPositionY(1, y - 2);
	std::uniform_int_distribution<int> enemyCount(2, 6);

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

			if (m_debug)
				std::cout << "Enemy spawn position: " << position << " Blocked: " << m_grid->GetValueAtLocation(position) << std::endl;

			if (currentRegionChunk == m_playerSpawnRegion)
			{
				if (m_grid->GetValueAtLocation(position) || position == m_playerSpawnLocation)
					continue;
				else
					movesAway = abs(position.x - m_playerSpawnLocation.x) + abs(position.y - m_playerSpawnLocation.y);
			}				
			else
			{
				if (m_grid->GetValueAtLocation(position))
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
					enemy = new Yeti(position, difficultyScale);
					break;
				case 'M':
					enemy = new Monolith(position, difficultyScale);
					break;
				case 'C':
					enemy = new Crawler(position, difficultyScale);
					break;
				case 'F':
					enemy = new FlameOfFury(position, difficultyScale);
					break;
				case 'E':
					enemy = new Exile(position, difficultyScale);
					break;
				default:
					std::cout << "I should never land here\n";
					enemy = new Enemy();
				}
				PrintIfDebug("New enemy added: " + enemy->GetName());
				m_chunk->AddEnemy(enemy);
				break;
			}
			rnd -= region->GetChoiceWeightAtIndex(i);
		}

		PrintIfDebug(std::to_string(m_chunk->GetEnemyVector().size()));
		PrintIfDebug(m_chunk->GetEnemyAtIndex(i)->GetName());
		
		m_grid->SetCharacterAtLocation(m_chunk->GetEnemyAtIndex(i));		
	}
}

