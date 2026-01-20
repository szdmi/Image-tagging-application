#pragma once

#include "button.h"
#include "Item.h"
#include "field.h"
#include <list>


enum STATUS {
	OFF = 0,
	ON = 1,
	WAIT = 2
};

enum ACTION {
	MOVER_MOVED = -2,
	NOTHING_SELECTED = -1
};

class scroll_menu
{
private:

	// menu propertiess
	sf::Vector2i Position = sf::Vector2i(0,0);
	sf::Vector2i Size = sf::Vector2i(0,0);
	short int numberOfItems = 0;
	short int curNumOfItems = 0;
	sf::Vector2i firstLastItem = sf::Vector2i(0,0);
	sf::Vector2i itempos = sf::Vector2i(0,0);
	sf::Vector2i startpos = sf::Vector2i(0, 0);

	// mover 

	button mover;
	short int moverPos = 0;
	short int moverSize = 0;
	short int mover_status = STATUS::OFF;

	// moverWay

	field moverWay;
	bool mouseLeftPressed = false;

	short int distance = 30;
	short int scrollPos = 0;
	short int upperBorder = 0;
	short int lowerBorder = 0;

	// items


	Item* item_count = nullptr;
	sf::Vector2i itemSize = sf::Vector2i(100,30);
	short int status = STATUS::OFF;
	int indent = 5;
	
	std::string* textList = nullptr;

	// dropdown 

	int drop_status = STATUS::OFF;
	bool dropdown = false;
	bool selected = false;
	button dropButton;



public:
	scroll_menu();		// currently not in use

	~scroll_menu();

	scroll_menu(short int number,sf::Vector2i menuSize, sf::Vector2i position, bool dropdown);

	void setText(int n, std::string txt);																// write text to n-th line of the list

	void setPosition(sf::Vector2i position);

	void setScale(sf::Vector2i menuSize);

	void setColour(int r, int g, int b, int whatColor);		// 1 - Btn_main 2 - Btn_sec 3 - Btn_sel 4 - item_main 5 - item_sel 6 - mvr_way

	void update(short int number, sf::Vector2i menuSize, sf::Vector2i position);

	void show(sf::RenderWindow &window);		

	short int move(short int y, short int moverWayLength);

	short int pressed(short int y,sf::Event mouse, sf::RenderWindow& window);

	void setSelected(bool set);

	






};

