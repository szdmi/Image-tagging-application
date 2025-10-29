#pragma once
#include <sfml\Graphics.hpp>


class field
{
private:
	sf::RectangleShape Field;
	//int mainColor[3]{90,90,90};

public:

	field();
	field(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window);
	void setPos(sf::Vector2i position);
	void setScale(sf::Vector2i scale);
	void show(sf::RenderWindow& window);
	void setColor(int r, int g, int b);
	unsigned int pressed(sf::RenderWindow& window);
};

