#include "button.h"
#include "C:\Users\slava\source\Csharp\Enigma\Enigma\font.h"
#include <cmath>
#include <iostream>

enum STATUS {
    OFF = 0,
    ON = 1,
    WAIT = 2
};

sf::Vector2f button::round(const sf::Vector2f vector)
{
    return sf::Vector2f{ std::round(vector.x), std::round(vector.y) };
}

button::button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, std::string T) {

    Button.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
    Button.setOrigin(float(scale.x/2), float(scale.y / 2));
    Button.setPosition(float(position.x),float(position.y));

    // outline
    Button.setOutlineThickness(5.f);
    Button.setOutlineColor(sf::Color(secColour[0], secColour[1], secColour[2]));
    
    // text
    font = loadFont(font);
    textstr << T;
    text.setString(textstr.str());
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(unsigned int(20));
    sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
    sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
    sf::Vector2f rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(float(position.x), float(position.y));
    text.setStyle(sf::Text::Bold);
};
//

button::button(sf::Vector2i scale, sf::Vector2i position, sf::RenderWindow& window, char Text[], unsigned int status) {

    Button.setSize(sf::Vector2f(float(scale.x), float(scale.y)));
    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
    Button.setOrigin(float(scale.x / 2), float(scale.y / 2));
    Button.setPosition(float(position.x), float(position.y));

    // outline
    Button.setOutlineThickness(5.f);
    Button.setOutlineColor(sf::Color(secColour[0], secColour[1], secColour[2]));

    // text
    font = loadFont(font);
    text.setString(Text);
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(unsigned int(20));
    sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
    sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
    sf::Vector2f rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(float(position.x), float(position.y));
    text.setStyle(sf::Text::Bold);
    status = STATUS::OFF;
};

button::button() {

    Button.setSize(sf::Vector2f(100.0f, 20.0f));
    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
    Button.setOrigin(Button.getSize().x/2, Button.getSize().y/2);
    Button.setPosition(100.0f, 150.0f);

    //outline
    Button.setOutlineThickness(5.f);
    Button.setOutlineColor(sf::Color(secColour[0], secColour[1], secColour[2]));

    // text
    font = loadFont(font);
    text.setString("Set text");
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(unsigned int(20));
    sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
    sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
    sf::Vector2f rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(100.f, 150.f);
    text.setStyle(sf::Text::Bold);
};

void button::setPosition(int x, int y) {

    Button.setPosition(sf::Vector2f(float(x), float(y)));
    text.setPosition(float(x) , float(y));
};

sf::Vector2f button::getSize() {
    return Button.getSize();
};

float button::getOutlineThickness() {
    return Button.getOutlineThickness();
}

void button::setScale(int x, int y) {

    Button.setSize(sf::Vector2f(float(x), float(y)));
    Button.setOrigin(float(x / 2), float(y / 2));
    text.setCharacterSize(unsigned int(20));
    //text.setOrigin(float(x/2), float(y/2));
    
    
};

void button::setText(std::string Text) {

    textstr.str("");
    textstr << Text;
    text.setString(textstr.str());

    sf::Vector2f center = text.getGlobalBounds().getSize() / 2.f;
    sf::Vector2f localBounds = center + text.getLocalBounds().getPosition();
    sf::Vector2f rounded = round(localBounds);
    text.setOrigin(rounded);
    text.setPosition(Button.getPosition());
};

std::string button::getText() {
    return text.getString();
};

void button::setColour(int r, int g, int b, int whatColour) {
    switch (whatColour) {
    case 1:
        mainColour[0] = r;          // 90 90 90 
        mainColour[1] = g;
        mainColour[2] = b;
        Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
        break;
    case 2:
        secColour[0] = r;           // 150 150 150 
        secColour[1] = g;
        secColour[2] = b;
        Button.setOutlineColor(sf::Color(secColour[0], secColour[1], secColour[2]));
        break;
    case 3:
        selColour[0] = r;           // 255, 120, 30
        selColour[1] = g;
        selColour[2] = b;
        break;
    }
};

void button::setOutlineThickness(int thikness) {
    Button.setOutlineThickness(thikness);

};

void button::changeColor(bool pressed) {

    if (pressed == true) {
        Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
    }
    else {
        Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
    }
}


void button::show(sf::RenderWindow& window) {

    window.draw(Button);
    window.draw(text);
}

bool button::isInBounds(sf::Vector2f BtnPosition, sf::RenderWindow& window) {
    if (abs(BtnPosition.x - float(sf::Mouse::getPosition(window).x)) < Button.getSize().x / 2.f) {
        if (abs(BtnPosition.y - float(sf::Mouse::getPosition(window).y)) < Button.getSize().y / 2.f) {
            return true;
        }
    }
    return false;
};


short int button::pressed1(short int status, sf::RenderWindow& window) {
    
    if (isInBounds(Button.getPosition(),window)) {
        Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));


        if (status == STATUS::WAIT) {
            return status;
        }
        else if (status == STATUS::OFF) {
            status = STATUS::ON;
        }
        else {
            status = STATUS::OFF;
        }
        return status;

    }
    return status;
    

};
short int button::pressed2(short int status, sf::Event event, sf::RenderWindow& window) {
    if (isInBounds(Button.getPosition(), window)) {
        Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));

        if (status == STATUS::WAIT && event.type == sf::Event::MouseButtonReleased) {
            return status = STATUS::OFF;
        }
        else if (status == STATUS::WAIT) {
            return status;
        }

        status = STATUS::ON;
        return status;


    }
    return STATUS::OFF;


};
short int button::pressed3(short int status, sf::RenderWindow& window) {
    if (isInBounds(Button.getPosition(), window)) {
        Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));

        if (status == STATUS::ON) {
            Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
            status = STATUS::OFF;
            return status;
        }
        status = STATUS::ON;
            return status;
    }
    return status;


};

short int button::pressed4(short int status,sf::Vector2f buttonpos, sf::RenderWindow& window) {
    if (isInBounds(buttonpos,window)) {

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
            if (status == STATUS::WAIT) {
                return status;
            }
            status = STATUS::ON;
            return status;
        }
    }
    
    return status = STATUS::OFF;


};

short int button::pressed(short int status, sf::Event event, sf::RenderWindow &window, bool mode) {

            
    switch (event.type) {

    case sf::Event::MouseButtonPressed:
        if (isInBounds(Button.getPosition(),window) ) {
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                btnIsPressed = true;
                if (status == STATUS::ON) {
                    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                    status = STATUS::OFF;
                    return status;
                }
                Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));
                status = STATUS::ON;
                return status;
            }
        }
        break;

    case sf::Event::MouseButtonReleased:
        if (mode == false) {
            if (btnIsPressed == true) {

                btnIsPressed = false;
                /*if (status == STATUS::ON) {
                    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                    status = STATUS::OFF;
                    return status;
                }*/
                Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                status = STATUS::OFF;
                return status;
            }
        }
        break;
    }
    return status;
    //return STATUS::OFF;
};

