#include "tag.h"
#include "C:\Users\slava\source\repos\ImageX\ImageX\font.h"



enum KEY {
	DELETE_KEY = 8,
	ENTER_KEY = 13,
	ESCAPE_KEY = 27
};

static int mainColour[3]{255,0,0};
static int secColour[3];
static int selColour[3]{250,130,140};

			// ======= private =======

void tag::inputLogic(int charTyped) {
	if (charTyped != KEY::DELETE_KEY && charTyped != KEY::ENTER_KEY && charTyped != KEY::ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
		length += 1.f;
	}
	else if (charTyped == KEY::DELETE_KEY) {
		if (text.str().length() > 0) {
			delLastChar();
		}
	}
	textbox.setString(text.str() + "_");
};

void tag::delLastChar() {
	std::string t = text.str();
	std::string newt = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newt += t[i];
	}
	text.str("");
	text << newt;

	textbox.setString(text.str());
	length -= 1.f;
};



			// ======= public =======

tag::tag() {
	convexdraw2(length);
	
	// text
	font = loadFont(font);
	textbox.setFont(font);
	textbox.setString("tag");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);
	isSelected = false;
	if (isSelected) {
		textbox.setString("_");
		convex.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
	}
	else {
		textbox.setString("");
		convex.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
	}

	
};

tag::tag(sf::Vector2i startpoint) {
	convexdraw(length);
	
	// text
	font = loadFont(font);
	textbox.setFont(font);
	textbox.setString("tag");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);

	isSelected = true;
	(isSelected) ? (textbox.setString("_")) : (textbox.setString(""));
};

tag::tag(std::string folder) {
	convexdraw2(length);

	// text
	font = loadFont(font);
	textbox.setFont(font);
	text << folder;
	textbox.setString(text.str());
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);
	isSelected = true;
	/*if (isSelected) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}*/
};

tag::~tag() {
	
};

void tag::operator = (const tag& other) {
	this->textbox.setString(other.textbox.getString());
	this->position = other.position;
	setPosition(position);
	//std::cout << "position " << other.position.x << std::endl;
	this->length = other.length;
	this->TagAdded = other.TagAdded;
	isSelected = other.isSelected;
}

void tag::tagshow(int i) {																										// allows tag to display
	TagAdded = i == 1;
}

void tag::show(sf::RenderWindow& window) {																						// display method
	if (TagAdded == true) {
		convexdraw(length);
		window.draw(convex);
		window.draw(textbox);
	}

};

void tag::show2(sf::RenderWindow& window) {																						// display method for scroll menues
	if (TagAdded == true) {
		convexdraw2(length);
		window.draw(convex);
		window.draw(textbox);
	}

};

void tag::setlength(float length) {
	this->length = length;
};

void tag::deleteTag() {
	text.str("");
	textbox.setString(text.str());
	isSelected = false;
	length = 1.f;
	tagshow(0);
}

void tag::select() {																											// selection of the tag
	if (isSelected == true) {
		isSelected = false;
	}
	else {
		isSelected = true;
	}
	/*
	* isSelected = isSelected == false;
	*/
}

bool tag::getselect() {
	return isSelected;
}

void tag::setSel(bool sel) {
	isSelected = sel;
	if (!sel) {
		std::string t = text.str();
		std::string newt = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newt += t[i];
		}
		textbox.setString(newt);
	}
}



void tag::setTxt(std::string st, sf::RenderWindow& window) {																	// set text
	textbox.setString(st);
	window.draw(textbox);

};

void tag::setColour(int r, int g, int b,int whatColour) {
	switch (whatColour) {
	case 1:
		mainColour[0] = r;
		mainColour[1] = g;
		mainColour[2] = b;
	case 2:
		secColour[0] = r;
		secColour[1] = g;
		secColour[2] = b;
	case 3:
		selColour[0] = r;
		selColour[1] = g;
		selColour[2] = b;
	}
};

std::string tag::getText() {																									// get text
	return text.str();
}

short int tag::typedOn(sf::Event input) {																						// main keyboard input function
	if (isSelected) {
		int chartyped = input.text.unicode;
		if (chartyped < 128) {
			if (chartyped == KEY::ENTER_KEY) {
				textbox.setString(text.str() + "");
				isSelected = false;
				return 0;
			}
			else if (text.str().length() <= 8) {
				inputLogic(chartyped);

			}
			else if (text.str().length() > 8 && chartyped == KEY::DELETE_KEY) {
				inputLogic(chartyped);
			}
		}
		return 1;
	}
	return 0;
}

void tag::setPosition(sf::Vector2i Pos) {																						// set position 
	position.x = Pos.x;
	position.y = Pos.y;
	convex.setPosition(sf::Vector2f(float(position.x), float(position.y)));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
};

const sf::Vector2i tag::getPosition() {																							// get position
	return position;
};

const float tag::getlength() {																									// returns lenght of the tag`s body
	if (length > 4) {
		return(60.f + (length-3) * 13.f);
	}
	else {
		return(73.f);
	}
};

void tag::convexdraw(float taglength) {																							// tag`s body drawing method

	(taglength > 4) ? (taglength = (taglength - 3) * 13.f) : (taglength = 13.f);
	
	convex.setPointCount(6);
	convex.setPoint(0, sf::Vector2f(0.f, 30.f));
	convex.setPoint(1, sf::Vector2f(0.f, 5.f));
	convex.setPoint(2, sf::Vector2f(5.f, 0.f));
	convex.setPoint(3, sf::Vector2f(40.f+taglength, 0.f));
	convex.setPoint(4, sf::Vector2f(40.f+taglength, 25.f));
	convex.setPoint(5, sf::Vector2f(35.f+taglength, 30.f));
	if (isSelected == true) {
		convex.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
	}
	else {
		convex.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
	}
	convex.setOrigin(sf::Vector2f(0.f, 15.f));
	//std::cout << "set origin called" << convex.getOrigin().y << std::endl;
}

void tag::convexdraw2(float length) {																										// tag`s body drawing method for scroll menues

	convex.setPointCount(6);
	convex.setPoint(0, sf::Vector2f(0.f, 29.f));
	convex.setPoint(1, sf::Vector2f(0.f, 6.f));
	convex.setPoint(2, sf::Vector2f(5.f, 1.f));
	convex.setPoint(3, sf::Vector2f(length , 1.f));
	convex.setPoint(4, sf::Vector2f(length , 24.f));
	convex.setPoint(5, sf::Vector2f(length - 5.f, 29.f));
	convex.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
	convex.setOrigin(sf::Vector2f(0.f, 15.f));
}

short int tag::pressed3(short int status, sf::RenderWindow& window) {															// selection of the tag by mouse ( currently not in use )

	if (abs(convex.getPosition().x + length / 2 - float(sf::Mouse::getPosition(window).x)) < length/2) {
		if (abs(convex.getPosition().y - float(sf::Mouse::getPosition(window).y)) < 15) {
			convex.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
			/*std::cout << Button.getPosition().y << std::endl;             // checks positions of mouse and button
			std::cout << float(sf::Mouse::getPosition().y - window.getPosition().y) << std::endl;
			std::cout << Button.getOrigin().y << std::endl;
			std::cout << Button.getSize().y << std::endl;*/
			if (status == 2) {
				return status;
			}
			status = 1;
			return status;

		}
	}
	return 0;


};

