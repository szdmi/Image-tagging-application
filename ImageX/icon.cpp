#include "icon.h"
#include "font.h"
#include <math.h>
#include <iostream>


icon::icon() {
	Icon.setSize(sf::Vector2f(200.f, 100.f));
	Icon.setOrigin(sf::Vector2f(Icon.getSize().x / 2.f, Icon.getSize().y / 2.f));
	Icon.setFillColor(sf::Color(150, 150, 150));
	Icon.setPosition(sf::Vector2f(960.f, 100.f));

	// text

	text.setString("Set text");
	font = loadFont(font);
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(unsigned int(20));
	text.setPosition(sf::Vector2f(860.f,50.f ));
	text.setStyle(sf::Text::Bold);

	text2.setString("Set res");
	text2.setFont(font);
	text2.setFillColor(sf::Color::Yellow);
	text2.setCharacterSize(unsigned int(20));
	text2.setPosition(sf::Vector2f(860.f, 70.f));
	text2.setStyle(sf::Text::Bold);
};

icon::icon(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string Text) {
	Icon.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
	Icon.setOrigin(sf::Vector2f(Icon.getSize().x / 2.f, Icon.getSize().y / 2.f));
	Icon.setFillColor(sf::Color(150, 150, 150));
	Icon.setPosition(sf::Vector2f(float(position.x), float(position.y)));

	// text

	text.setString(Text);
	font = loadFont(font);
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(unsigned int(20));
	text.setPosition(sf::Vector2f(float(position.x) - (Icon.getOrigin().x / 1.1), float(position.y) - (Icon.getOrigin().y )));
	text.setStyle(sf::Text::Bold);
}

icon::icon(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string Text, std::string Text2) {
	Icon.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
	Icon.setOrigin(sf::Vector2f(Icon.getSize().x / 2.f, Icon.getSize().y / 2.f));
	Icon.setFillColor(sf::Color(150, 150, 150));
	Icon.setPosition(sf::Vector2f(float(position.x), float(position.y)));

	// text

	text.setString(Text);
	font = loadFont(font);
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(unsigned int(20));
	text.setPosition(sf::Vector2f(float(position.x) - (Icon.getOrigin().x / 1.1), float(position.y) - (Icon.getOrigin().y / 2.f)));
	text.setStyle(sf::Text::Bold);

	text2.setString(Text2);
	text2.setFont(font);
	text2.setFillColor(sf::Color::White);
	text2.setCharacterSize(unsigned int(20));
	text2.setPosition(sf::Vector2f(float(position.x) - (Icon.getOrigin().x / 1.1), float(position.y) - (Icon.getOrigin().y / 2.f -20.f)));
	text2.setStyle(sf::Text::Bold);
};

void icon::show(sf::RenderWindow& window) {
	window.draw(Icon);
	window.draw(text);
	window.draw(text2);
};

void icon::settxt(std::string Text, std::string Text2, sf::RenderWindow& window) {
	text.setString(Text);
	text2.setString(Text2);
};
