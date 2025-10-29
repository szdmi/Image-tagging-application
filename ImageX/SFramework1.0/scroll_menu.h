#pragma once

#include "button.h"
#include "tag.h"
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
	sf::Vector2i Position = sf::Vector2i(0,0);
	sf::Vector2i Size;
	short int numberOfTags;
	short int curNumOfTags;
	sf::Vector2i firstLastTag = sf::Vector2i(0,0);

	sf::Vector2i tagpos = sf::Vector2i(0,30);

	button mover;
	short int moverPos;
	short int moverSize;
	short int mover_status = STATUS::OFF;
	field moverWay;
	bool mouseLeftPressed = false;

	short int distance = 30;
	short int scrollPos;
	short int upperBorder = 0;
	short int lowerBorder = 0;

	tag tags[100];
	tag* tagcount;
	short int status = STATUS::OFF;
	
	std::string* textList;

	// rolldown variables
	int drop_status = STATUS::OFF;
	bool dropdown;
	bool selected = false;
	button dropButton;



public:
	scroll_menu();		// currently not in use

	~scroll_menu();

	scroll_menu(short int number,sf::Vector2i menuSize, sf::Vector2i position, bool dropdown);

	void setText(int n, std::string txt);																// write text to n-th line of the list

	void setPosition(sf::Vector2i position);

	void setScale(sf::Vector2i menuSize);

	void setColour(int r, int g, int b, int whatColor);		// 1 - Btn_main 2 - Btn_sec 3 - Btn_sel 4 - tag_main 5 - tag_sel 6 - mvr_way

	void update(short int number, sf::Vector2i menuSize, sf::Vector2i position);

	void show(sf::RenderWindow &window);		

	short int move(short int y, short int moverWayLength);

	short int pressed(short int y,sf::Event mouse, sf::RenderWindow& window);

	






};

