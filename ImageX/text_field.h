#pragma once
#include <sfml\Graphics.hpp>
#include <sstream>
#include <iostream>


class text_field
{
private:
	sf::RectangleShape Text_field;
	sf::Font font;
	sf::Text textbox;
	sf::Vector2i position;
	std::ostringstream text;
	bool isSelected;
	int limit = 10;

	sf::Color color;

	void delLastChar();														// stuff for keyboard input

	void inputLogic(int charTyped);											// stuff for keyboard input


public:

	text_field();
	
	text_field(sf::Vector2i scale, sf::Vector2i position);
	
	void setPosition(sf::Vector2i position);
	
	const sf::Vector2i getPosition();
	
	void setScale(sf::Vector2i scale);
	
	void show(sf::RenderWindow& window);
	
	void setColor(int r, int g, int b);
	
	void setTextColor(int r, int g, int b);
	
	void setTransparent(bool set);
	
	void setText(std::string st, sf::RenderWindow& window);

	bool getSelected();

	void setSelected(bool select);
	
	std::string getText();

	short int typedOn(sf::Event input);

	short int pressed3(short int status, sf::RenderWindow& window);
};

