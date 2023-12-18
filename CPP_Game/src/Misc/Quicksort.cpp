#include "Quicksort.h"

void QuicksortAbility(std::vector<std::shared_ptr<Ability>> abilities)
{
	int pivot = abilities.at(abilities.size() - 1)->GetCooldown();
	int counter;
	for (counter = 0; counter < abilities.size(); counter++)
	{
		if (abilities.at(counter)->GetCooldown() > pivot)
			break;
	}
}
