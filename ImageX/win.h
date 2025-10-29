#pragma once
#include <sfml\Graphics.hpp>
//#include "tag.h"
#include "button.h"
//#include "scroll_menu.h"

//#include "font.h"
//#include <cmath>
class win
{

private:
	sf::Vector2i winsize;
	sf::Text text;
	sf::Font font;
	std::ostringstream textstr;
	bool winIsOpen = false;
	//sf::RenderWindow Window(sf::VideoMode(winsize), "Select folder", sf::Style::Default);
	sf::RenderWindow Window;
	short int status = 0;
	//tag* image;
	//tag images[100];
	void winclear() {
		Window.clear(sf::Color(70, 70, 70));
	}

public:

	win();

	win(sf::Vector2i winsize, std::string textbox);

	short int winprocess();

	//void ()

};