#pragma once
#include <sfml\Graphics.hpp>
#include <sstream>
#include <iostream>



class tag
{
private:
	sf::ConvexShape convex;													// tag`s body
	sf::Font font;
	sf::Text textbox;
	std::ostringstream text;
	sf::Vector2i position;
	bool isSelected;
	int limit = 10;															// characters limit
	float length = 1.f;														// tag`s  length multiplyer
	bool TagAdded = false;													// allows tag to display (used for static array of tags)
	

	void inputLogic(int charTyped);											// stuff for keyboard input

	void delLastChar();														// stuff for keyboard input
	
	
public:
	
	tag();

	tag(sf::Vector2i startpoint);

	tag(std::string folder);

	~tag();

	void operator = (const tag& other);

	void show(sf::RenderWindow& window);									// display method

	void show2(sf::RenderWindow& window);									// display method for scroll menues

	void setlength(float length);

	void setTxt(std::string st, sf::RenderWindow& window);

	void setColour(int r, int g, int b, int whatColour);

	void setSel(bool sel);													// 

	std::string getText();

	short int typedOn(sf::Event input);										// another stuff for keyboard

	void select();

	bool getselect();

	void setPosition(sf::Vector2i);

	const sf::Vector2i getPosition();

	const float getlength();												// length of the tag`s body

	void convexdraw(float length);											// method to draw tag`s body

	void convexdraw2(float length);														// method to draw tag`s body for sroll menues

	void tagshow(int i);													// allows tag to display (for static arrays usage)

	void deleteTag();														// delete tag 

	short int pressed3(short int status, sf::RenderWindow& window);			// function for selecting the tag (currently not in use)
};

