#include "Item.h"
#include "C:\Users\slava\source\repos\ImageX\ImageX\SFramework1.0\fonts\font.h"

static sf::Font font;

void Item::loadItemFont() {
	font = loadFont(font);

};

static int mainColour[3]{ 255,0,0 };
static int secColour[3];
static int selColour[3]{ 250,130,140 };


// ======= public =======

Item::Item() {
	convexDraw(true);

	// text
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

Item::Item(sf::Vector2i startpoint) {
	convexDraw(false);

	// text
	textbox.setFont(font);
	textbox.setString("tag");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);

	isSelected = false;
	(isSelected) ? (textbox.setString("_")) : (textbox.setString(""));
};

Item::Item(std::string tagName) {
	convexDraw(false);

	// text
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

Item::~Item() {

};

void Item::operator = (const Item& other) {
	this->textbox.setString(other.textbox.getString());
	this->position = other.position;
	setPosition(position);
	//std::cout << "position " << other.position.x << std::endl;
	this->conv_size = other.conv_size;
	isSelected = other.isSelected;
}



void Item::show(sf::RenderWindow& window, bool fixedLength) {																						// display method

		if (fixedLength == false) {
			convexDraw(false);
		}
		else {
			convexDraw(true);
		}
		window.draw(convex);
		window.draw(textbox);

};

void Item::setSize(sf::Vector2i size) {
	this->conv_size = size;
};


void Item::select() {																											// selection of the tag
	if (isSelected == true) {
		isSelected = false;
	}
	else {
		isSelected = true;
	}
}

bool Item::getSelected() {
	return isSelected;
}

void Item::setSelected(bool select) {
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

void Item::deleteItem() {
	text.str("");
	textbox.setString(text.str());
	isSelected = false;
}

void Item::setText(std::string st, sf::RenderWindow& window) {																	// set text
	textbox.setString(st);
	window.draw(textbox);

};

void Item::setColour(int r, int g, int b, int whatColour) {
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

std::string Item::getText() {																									// get text
	return text.str();
}

void Item::setPosition(sf::Vector2i Pos) {																						// set position 
	position.x = Pos.x;
	position.y = Pos.y;
	convex.setPosition(sf::Vector2f(float(position.x), float(position.y)));
	textbox.setPosition(convex.getPosition().x - (convex.getOrigin().x / 2.f), convex.getPosition().y - (convex.getOrigin().y / 2.f));
};

const sf::Vector2i Item::getPosition() {																							// get position
	return position;
};

const sf::Vector2i Item::getSize() {
	return conv_size;
};

void Item::convexDraw(bool fixed_length) {																							// tag`s body drawing method
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

short int Item::pressed3(short int status, sf::RenderWindow& window) {															// selection of the tag by mouse ( currently not in use )
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

