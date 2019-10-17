#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include "Point.h"
class State
{
public:
	State();
	std::vector<int > points;
	float fitness;
	
};

