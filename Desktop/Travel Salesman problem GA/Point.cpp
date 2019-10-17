#include "Point.h"



Point::Point()
{
}

void Point::setPos(sf::Vector2f pos)
{
	this->pos = pos;
}

sf::Vector2f Point::getPos()
{
	return pos;
}


