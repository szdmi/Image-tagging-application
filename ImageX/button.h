#pragma once
#include <sstream>
#include <sfml\Graphics.hpp>
class button
{
private:
	sf::RectangleShape Button;
	sf::Text text;
	sf::Font font;
	
	std::ostringstream textstr;
	//sf::Vector2i position;
	//sf::Vector2i scale;

	int mainColour[3]{90,90,90};
	int secColour[3]{ 255, 120, 30 };
	int selColour[3]{150,150,150};

public:
	button();
	button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string T);
	button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, char Text[], unsigned int status);

	void setpos(int x, int y);

	void setscale(int x, int y);

	void settext(std::string Text);

	void setColour(int r, int g, int b, int whatColour);		// 1 - main 2 - sec 3 - sel

	void changeColor(bool pressed);

	void show(sf::RenderWindow& window);

	short int pressed1(short int status); // hold button
	short int pressed2(short int status, sf::Event event); // usual button
	short int pressed3(short int status, sf::RenderWindow& window); // for secondary windows
	short int pressed4(short int status,sf::Vector2i buttonpos, sf::RenderWindow& window); // for scroll menues
	short int pressed(short int status, bool mode, sf::RenderWindow& window); // for everything (mode: false - click without bonding, true - with it)
};

