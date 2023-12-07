#include "../Header/Crawler.h"

Crawler::Crawler(int2 position)
	:Enemy(30,6,'C', "Crawler", position, Earth)
{
	m_xpDrop = 20;
}