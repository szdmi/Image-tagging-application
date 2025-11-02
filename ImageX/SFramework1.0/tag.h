#pragma once
#include <sfml\Graphics.hpp>
#include <sstream>
#include <iostream>



class tag
{
private:
	sf::ConvexShape convex;													// tag`s body
	sf::Vector2i conv_size = sf::Vector2i(100,30);
	sf::Font font;
	sf::Text textbox;
	std::ostringstream text;
	sf::Vector2i position;
	bool isSelected;
	int limit = 10;															// characters limit
	bool ignore = false;													// allows tag to display (used for static array of tags)

	
	

	void inputLogic(int charTyped);											// stuff for keyboard input

	void delLastChar();														// stuff for keyboard input

	void convexDraw( bool fixed_length);											// method to draw tag`s body

	//void convexDraw2(float length);											// for sroll menues
	
	
public:
	
	tag();

	tag(sf::Vector2i startpoint);

	tag(std::string tagName);

	~tag();

	void operator = (const tag& other);

	void show(sf::RenderWindow& window, bool fixedLength);									

	void setSize(sf::Vector2i);

	void setText(std::string st, sf::RenderWindow& window);

	void setColour(int r, int g, int b, int whatColour);

	void setSelected(bool select);											

	std::string getText();

	short int typedOn(sf::Event input);										

	void select();															// change select (true => false, and vice versa)

	bool getSelected();

	void setPosition(sf::Vector2i);

	const sf::Vector2i getPosition();

	const sf::Vector2i getSize();												// length of the tag`s body (in characters)

	void showIgnore(int i);													// (for static arrays usage)

	void deleteTag();														

	short int pressed3(short int status, sf::RenderWindow& window);			
};

