#include "../Header/Crawler.h"

Crawler::Crawler(int2 position)
	:Enemy(30,6,'C', "Crawler", position, Earth)
{
	m_xpDrop = 20;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Claw>());
}