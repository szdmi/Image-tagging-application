#include "field.h"
#include <cmath>
#include <iostream>

enum STATUS {
	OFF = 0,
	ON = 1,
	WAIT = 2
};


field::field() {
	Field.setSize(sf::Vector2f(100.0f, 100.0f));
	Field.setOrigin(sf::Vector2f(Field.getSize().x / 2.f, Field.getSize().y / 2.f));
	Field.setFillColor(sf::Color(90, 90, 90));
	Field.setPosition(sf::Vector2f(1920.0f / 2.f, 1080.f / 2.f));

}

field::field(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window) {
	Field.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
	Field.setOrigin(sf::Vector2f(Field.getSize().x / 2.f, Field.getSize().y / 2.f));
	Field.setFillColor(sf::Color(90, 90, 90));
	Field.setPosition(sf::Vector2f(float(position.x), float(position.y)));

}

void field::setPosition(sf::Vector2i position) {
	Field.setPosition(sf::Vector2f(float(position.x), float(position.y)));
};

void field::setScale(sf::Vector2i scale) {
	Field.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
	Field.setOrigin(sf::Vector2f(Field.getSize().x / 2.f, Field.getSize().y / 2.f));
};

void field::show(sf::RenderWindow& window) {
	window.draw(Field);
}

void field::setColor(int r, int g, int b) {
	
	Field.setFillColor(sf::Color(r, g, b));
};

unsigned int field::pressed(sf::RenderWindow& window) {
	unsigned int status = STATUS::OFF;
	if ((abs(Field.getPosition().x - float((sf::Mouse::getPosition()).x))) < Field.getSize().x / 2.f) {
		if ((abs(Field.getPosition().y - float((sf::Mouse::getPosition()).y))) < Field.getSize().y / 2.f) {
			Field.setFillColor(sf::Color::White);
			return status;
		}
	}
};