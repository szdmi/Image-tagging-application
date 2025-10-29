#include "text_field.h"
#include "font.h"

enum KEY {
	DELETE_KEY = 8,
	ENTER_KEY = 13,
	ESCAPE_KEY = 27
};

void text_field::inputLogic(int charTyped) {
	if (charTyped != KEY::DELETE_KEY && charTyped != KEY::ENTER_KEY && charTyped != KEY::ESCAPE_KEY) {
		text << static_cast<char>(charTyped);
		//length += 1.f;
	}
	else if (charTyped == KEY::DELETE_KEY) {
		if (text.str().length() > 0) {
			delLastChar();
		}
	}
	textbox.setString(text.str() + "_");
};

void text_field::delLastChar() {
	std::string t = text.str();
	std::string newt = "";
	for (int i = 0; i < t.length() - 1; i++) {
		newt += t[i];
	}
	text.str("");
	text << newt;

	textbox.setString(text.str());
	//length -= 1.f;
};

text_field::text_field() {
	Text_field.setSize(sf::Vector2f(100.0f, 100.0f));
	Text_field.setOrigin(sf::Vector2f(Text_field.getSize().x / 2.f, Text_field.getSize().y / 2.f));
	Text_field.setFillColor(sf::Color(90, 90, 90));
	Text_field.setPosition(sf::Vector2f(100.0f / 2.f, 100.f / 2.f));
	this->position.x = 100.0f / 2.f;
	this->position.y = 100.0f / 2.f;

	font = loadFont(font);
	textbox.setFont(font);
	textbox.setString("Enter text...");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(Text_field.getPosition().x - (Text_field.getOrigin().x), Text_field.getPosition().y - (Text_field.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);
	isSelected = false;
	if (isSelected) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}
};

text_field::text_field(sf::Vector2i scale, sf::Vector2i position) {
	this->position.x = position.x;
	this->position.y = position.y;
	Text_field.setSize(sf::Vector2f(scale.x, scale.y));
	Text_field.setOrigin(sf::Vector2f(Text_field.getSize().x / 2.f, Text_field.getSize().y / 2.f));
	Text_field.setFillColor(sf::Color(90, 90, 90));
	Text_field.setPosition(sf::Vector2f(position.x, position.y));

	font = loadFont(font);
	textbox.setFont(font);
	textbox.setString("Enter text...");
	textbox.setFillColor(sf::Color::White);
	textbox.setCharacterSize(unsigned int(15));
	textbox.setPosition(Text_field.getPosition().x - (Text_field.getOrigin().x), Text_field.getPosition().y - (Text_field.getOrigin().y / 2.f));
	textbox.setStyle(sf::Text::Bold);
	isSelected = false;
	if (isSelected) {
		textbox.setString("_");
	}
	else {
		textbox.setString("");
	}
};

void text_field::setPosition(sf::Vector2i position) {
	this->position.x = position.x;
	this->position.y = position.y;
	Text_field.setPosition(sf::Vector2f(position.x, position.y));
	textbox.setPosition(Text_field.getPosition().x - (Text_field.getOrigin().x), Text_field.getPosition().y - (Text_field.getOrigin().y / 2.f));
};

const sf::Vector2i text_field::getPosition() {
	return position;
};

void text_field::setScale(sf::Vector2i scale) {
	Text_field.setSize(sf::Vector2f(100.0f, 100.0f));
	Text_field.setOrigin(sf::Vector2f(Text_field.getSize().x / 2.f, Text_field.getSize().y / 2.f));
};

void text_field::show(sf::RenderWindow& window) {
	window.draw(Text_field);
	window.draw(textbox);
};

void text_field::setColor(int r, int g, int b) {
	Text_field.setFillColor(sf::Color(r, g, b));
};

void text_field::setTextColor(int r, int g, int b) {
	textbox.setFillColor(sf::Color(r, g, b));
	
};

void text_field::setTransparent(bool set) {
	if (set) {
		Text_field.setFillColor(sf::Color::Transparent);
		color = Text_field.getFillColor();
	}
	else {
		Text_field.setFillColor(color);
	}
};

void text_field::setText(std::string st, sf::RenderWindow& window) {
	textbox.setString(st);
	window.draw(textbox);
};

std::string text_field::getText() {
	return text.str();													// text.str();		??????
};

bool text_field::getSelected() {
	return isSelected;
}

void text_field::setSelected(bool select) {
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

short int text_field::typedOn(sf::Event input) {																						// main keyboard input function
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

short int text_field::pressed3(short int status, sf::RenderWindow& window) {															// selection of the tag by mouse ( currently not in use )
	if (abs(position.x - float(sf::Mouse::getPosition(window).x)) < Text_field.getSize().x / 2.f) {
		if (abs(position.y - float(sf::Mouse::getPosition(window).y)) < Text_field.getSize().y / 2.f) {
			if (status == 2) {
				return status;
			}
			status = 1;
			return status;

		}
	}
	return 0;


};