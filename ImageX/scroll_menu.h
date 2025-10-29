#pragma once
#include <sfml\Graphics.hpp>
#include "button.h"
#include "tag.h"
#include "field.h"


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
	short int numberOfTags;      // Количество тегов
	short int curNumOfTags;
	//bool mode;
	sf::Vector2i firstLastTag = sf::Vector2i(0,0);
	short int scrollPos;
	short int moverPos;
	short int moverSize;
	short int distance = 30;
	short int upperBorder = 0;
	short int lowerBorder = 0;
	//short int winsizeY;
	short int status = 0;
	sf::Vector2i winsize;
	sf::Vector2i tagpos = sf::Vector2i(0,30);
	button mover;
	field moverWay;

	tag tags[100];
	tag* tagcount;
	std::string* textList;

	// rolldown variables
	int status2 = 0;
	bool dropdown;
	bool selected = false;
	button selected_element;

	

	



public:
	scroll_menu();		// currently not in use

	~scroll_menu();

	scroll_menu(short int number,sf::Vector2i menuSize, sf::Vector2i position, bool dropdown);

	void general(short int number, sf::Vector2i menuSize, sf::Vector2i position);

	void setTxt(int n, std::string txt);

	void setPosition(sf::Vector2i position, sf::Vector2i menuSize);

	void update(short int number, sf::Vector2i menuSize, sf::Vector2i position);

	void setColour(int r, int g, int b, int whatColor);		// 1 - Btn_main 2 - Btn_sec 3 - Btn_sel 4 - tag_main 5 - tag_sel 6 - mvr_way

	void show(sf::RenderWindow &window);		

	short int move(short int y, short int moverWayLength);

	short int pressed(short int y,sf::Event mouse, sf::RenderWindow& window);

	






};

