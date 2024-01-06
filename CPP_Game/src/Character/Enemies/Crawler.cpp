#include "../Header/Crawler.h"

Crawler::Crawler(int2 position, double scaler)
	:Enemy(30 * scaler, 6 * (1 + (scaler - 1) * 0.5), 'C', "Crawler", position, Earth)
{
	m_xpDrop = 20 * scaler;
	FillAbilitiesWithPlaceholders(std::make_shared<Placeholder>());
	LearnAbility(std::make_shared<Claw>());
}