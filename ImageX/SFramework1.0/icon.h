#pragma once
#include <sfml\Graphics.hpp>


class icon
{
private:
	sf::RectangleShape Icon;
	sf::Font font;
	sf::Text text;
	sf::Text text2;
	sf::Vector2f round(const sf::Vector2f vector);
	int charSize = 20;
public:
	icon();
	icon(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string Text);
	icon(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string Text, std::string Text2);

	void show(sf::RenderWindow& window);
	void setText(std::string Text, std::string Text2, sf::RenderWindow& window);

	friend void loadFont();
};

