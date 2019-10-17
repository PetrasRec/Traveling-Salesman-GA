#include <iostream>
#include <ctime>
#include "Agent.h"

int main()
{
	srand(time(NULL));
	Agent agent;
	agent.gameLoop();

	return 0;
}