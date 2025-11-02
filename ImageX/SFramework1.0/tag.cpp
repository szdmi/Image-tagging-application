#include "tag.h"
#include "C:\Users\slava\source\repos\ImageX\ImageX\SFramework1.0\fonts\font.h"



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

};



			// ======= public =======

tag::tag() {
	convexDraw(true);
	
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
	convexDraw( false);
	
	// text
	font = loadFont(font);
	textbox.setFont(font);
	textbox.setString("tag");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);

	isSelected = false;
	(isSelected) ? (textbox.setString("_")) : (textbox.setString(""));
};

tag::tag(std::string tagName) {
	convexDraw(false);

	// text
	font = loadFont(font);
	textbox.setFont(font);
	text << tagName;
	textbox.setString(text.str());
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);
	isSelected = false;
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
	this->conv_size = other.conv_size;
	this->ignore = other.ignore;
	isSelected = other.isSelected;
}

void tag::showIgnore(int i) {																										// allows tag to display
	ignore = i == 1;
}

void tag::show(sf::RenderWindow& window , bool fixedLength) {																						// display method
	if (ignore == true) {
		if (fixedLength == false) {
			convexDraw( false);
		}
		else {
			convexDraw( true);
		}
		window.draw(convex);
		window.draw(textbox);
	}

};

void tag::setSize(sf::Vector2i size) {
	this->conv_size = size;
};

void tag::deleteTag() {
	text.str("");
	textbox.setString(text.str());
	isSelected = false;
	//length = 10.f;
	showIgnore(0);
}

void tag::select() {																											// selection of the tag
	if (isSelected == true) {
		isSelected = false;
	}
	else {
		isSelected = true;
	}
}

bool tag::getSelected() {
	return isSelected;
}

void tag::setSelected(bool select) {
	isSelected = select;
	if (!select) {
		std::string t = text.str();
		std::string newt = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newt += t[i];
		}
		textbox.setString(newt);
	}
	else {
		std::string t = text.str();
		std::string newt = "";
		for (int i = 0; i < t.length(); i++) {
			newt += t[i];
		}
		newt += "_";
		textbox.setString(newt);
	}
}



void tag::setText(std::string st, sf::RenderWindow& window) {																	// set text
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

const sf::Vector2i tag::getSize() {
	return conv_size;
};

void tag::convexDraw(bool fixed_length) {																							// tag`s body drawing method
	float minLength = 0.f;
	

	if (fixed_length == false) {
		conv_size.x = minLength + textbox.getGlobalBounds().getSize().x;
	}

	convex.setPointCount(6);
	convex.setPoint(0, sf::Vector2f(0.f, conv_size.y));
	convex.setPoint(1, sf::Vector2f(0.f, 5.f));
	convex.setPoint(2, sf::Vector2f(5.f, 0.f));
	convex.setPoint(3, sf::Vector2f(conv_size.x, 0.f));
	convex.setPoint(4, sf::Vector2f(conv_size.x, conv_size.y - 5));
	convex.setPoint(5, sf::Vector2f(conv_size.x - 5.f, conv_size.y));
	if (isSelected == true) {
		convex.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
	}
	else {
		convex.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
	}
	convex.setOrigin(sf::Vector2f(0.f, 15.f));
}

//void tag::convexDraw2(float length) {																										// tag`s body drawing method for scroll menues
//
//	convex.setPointCount(6);
//	convex.setPoint(0, sf::Vector2f(0.f, 29.f));
//	convex.setPoint(1, sf::Vector2f(0.f, 6.f));
//	convex.setPoint(2, sf::Vector2f(5.f, 1.f));
//	convex.setPoint(3, sf::Vector2f(length , 1.f));
//	convex.setPoint(4, sf::Vector2f(length , 24.f));
//	convex.setPoint(5, sf::Vector2f(length - 5.f, 29.f));
//	convex.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
//	convex.setOrigin(sf::Vector2f(0.f, 15.f));
//}

short int tag::pressed3(short int status, sf::RenderWindow& window) {															// selection of the tag by mouse ( currently not in use )
	if (abs(convex.getPosition().x + conv_size.x / 2 - float(sf::Mouse::getPosition(window).x)) < conv_size.x / 2) {
		if (abs(convex.getPosition().y - float(sf::Mouse::getPosition(window).y)) < 15) {
			convex.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
			if (status == 2) {
				return status;
			}
			status = 1;
			return status;

		}
	}
	return 0;


};

