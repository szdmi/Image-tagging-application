#include "icon.h"
#include "C:\Users\slava\source\repos\ImageX\ImageX\SFramework1.0\fonts\font.h"
#include <math.h>
#include <iostream>


sf::Vector2f icon::round(const sf::Vector2f vector)
{
	return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

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
	text.setCharacterSize(charSize);
	sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
	sf::Vector2f rounded = round(localBounds);
	text.setOrigin(rounded);
	text.setPosition(sf::Vector2f(960.f, 100.f - rounded.y));
	text.setStyle(sf::Text::Bold);

	text2.setString("Set text 2");
	text2.setFont(font);
	text2.setFillColor(sf::Color::Yellow);
	text2.setCharacterSize(charSize);
	sf::Vector2f center2 = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds2 = center2 + text.getLocalBounds().getPosition();
	sf::Vector2f rounded2 = round(localBounds2);
	text2.setOrigin(rounded2);
	text2.setPosition(sf::Vector2f(960.f, 100.f + rounded.y));
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
	text.setCharacterSize(unsigned int(charSize));
	sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
	sf::Vector2f rounded = round(localBounds);
	text.setOrigin(rounded);
	text.setPosition( sf::Vector2f(float(position.x), float(position.y)) );

	//text.setPosition(sf::Vector2f(float(position.x) - (Text.length()*charSize/2), float(position.y) - (charSize/2 )));
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
	text.setCharacterSize(charSize);
	sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
	sf::Vector2f rounded = round(localBounds);
	text.setOrigin(rounded);
	text.setPosition(sf::Vector2f(float(position.x), float(position.y) - rounded.y));
	text.setStyle(sf::Text::Bold);

	text2.setString(Text2);
	text2.setFont(font);
	text2.setFillColor(sf::Color::White);
	text2.setCharacterSize(charSize);
	sf::Vector2f center2 = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds2 = center2 + text.getLocalBounds().getPosition();
	sf::Vector2f rounded2 = round(localBounds2);
	text2.setOrigin(rounded2);
	text2.setPosition(sf::Vector2f(float(position.x), float(position.y) + rounded.y));
	text2.setStyle(sf::Text::Bold);
};

void icon::show(sf::RenderWindow& window) {
	window.draw(Icon);
	window.draw(text);
	window.draw(text2);
};

void icon::setText(std::string Text, std::string Text2, sf::RenderWindow& window) {
	

	int maxlength = int((Icon.getSize().x) / text.getCharacterSize());
	if (Text.length() > maxlength) {
		std::string tmp = "";
		for (int i = 0; i < maxlength-3; i++) {
			tmp += Text[i];
		}
		tmp += "...";
		Text = tmp;
	}

	if (Text2.length() > maxlength) {
		std::string tmp = "";
		for (int i = 0; i < maxlength - 3; i++) {
			tmp += Text2[i];
		}
		tmp += "...";
		Text2 = tmp;
	}

	text.setString(Text);

	sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
	sf::Vector2f rounded = round(localBounds);
	text.setOrigin(rounded);

	text2.setString(Text2);

	sf::Vector2f center2 = text.getGlobalBounds().getSize() / 2.f;
	sf::Vector2f localBounds2 = center2 + text.getLocalBounds().getPosition();
	sf::Vector2f rounded2 = round(localBounds2);
	text2.setOrigin(rounded2);
};
