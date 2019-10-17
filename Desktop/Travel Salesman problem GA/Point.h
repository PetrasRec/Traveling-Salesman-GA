#pragma once
#include <SFML/Graphics.hpp>

class Point
{
public:
	Point();
	void setPos(sf::Vector2f pos);
	sf::Vector2f getPos();
private:
	sf::Vector2f pos;
};

