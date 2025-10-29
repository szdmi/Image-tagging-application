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
	float length = 100.f;														// tag`s  length multiplyer
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

	void setTaglength(float length);

	void setText(std::string st, sf::RenderWindow& window);

	void setColour(int r, int g, int b, int whatColour);

	void setSelected(bool select);											

	std::string getText();

	short int typedOn(sf::Event input);										

	void select();															// change select (true => false, and vice versa)

	bool getSelected();

	void setPosition(sf::Vector2i);

	const sf::Vector2i getPosition();

	const float getTagLength();												// length of the tag`s body (in characters)

	void showIgnore(int i);													// (for static arrays usage)

	void deleteTag();														

	short int pressed3(short int status, sf::RenderWindow& window);			
};

