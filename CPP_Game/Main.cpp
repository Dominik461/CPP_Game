#include <iostream>
#include "src/Math/Int2.h"
#include "src/Math/Grid.h"
#include "src/Game.h"
#include "GameParameters.h"

int main()
{
		
	//EXAMPLES FOR EXERCISE 4

	//player wins
	std::cout << RunGame({ {'d', 'd', 'w', 'w', 'a', 'a', 'h', 'a', 'a'}, 3,8,10,4,10, int2(2,2), int2(4,4), 12, 10, false }) << std::endl;
	/*
	//player loses
	std::cout << RunGame({ {'w', 'w', 'd','d', 'd', 'w', 'w', 'd', 'd', 'd', 'd', 'd', 'a', 'a', 'a', 'a', 'a'}, 3,8,10,4,10, int2(0,0), int2(8,4), 12, 10, false }) << std::endl;

	//nothing happens -> player does not encounter enemy
	std::cout << RunGame({ {'w', 'w', 'd','d', 'd', 'w', 'w', 'd', 'd', 's', 's', 'd', 'a', 'a', 'a', 's', 's'}, 3,8,10,4,10, int2(0,0), int2(8,4), 12, 10, false }) << std::endl;

	//manually play
	std::cout << RunGame({ {}, 3,8,10,4,10, int2(2,2), int2(4,4), 12, 10, true }) << std::endl;
	*/
	

	return 0;
}
