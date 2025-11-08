#pragma once
#include <sstream>
#include <sfml\Graphics.hpp>
class button
{
private:
	sf::RectangleShape Button;
	sf::Text text;
	bool btnIsPressed = false;
	
	std::ostringstream textstr;
	//sf::Vector2i position;
	//sf::Vector2i scale;

	int mainColour[3]{90,90,90};
	int secColour[3]{ 255, 120, 30 };
	int selColour[3]{150,150,150};

	sf::Vector2f round(const sf::Vector2f vector);

	bool isInBounds(sf::Vector2f BtnPosition, sf::RenderWindow& window);

public:
	button();
	button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string T);
	button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, char Text[], unsigned int status);

	static void loadButtonFont();

	void setPosition(int x, int y);

	sf::Vector2f getSize();

	float getOutlineThickness();

	void setScale(int x, int y);

	void setText(std::string Text);

	std::string getText();

	void setColour(int r, int g, int b, int whatColour);		// 1 - main 2 - sec 3 - sel

	void setOutlineThickness(int thikness);

	void changeColor(bool pressed);

	void show(sf::RenderWindow& window);

	short int pressed1(short int status, sf::RenderWindow &window); // hold button
	short int pressed2(short int status, sf::Event event, sf::RenderWindow& window); // usual button
	short int pressed3(short int status, sf::RenderWindow& window); // for secondary windows
	short int pressed4(short int status,sf::Vector2f buttonpos, sf::RenderWindow& window); // for scroll menues
	short int pressed(short int status, sf::Event event, sf::RenderWindow& window, bool mode); // for everything (mode: false - click without bonding, true - with it)
};

