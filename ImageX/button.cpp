#include "button.h"
#include "C:\Users\slava\source\Csharp\Enigma\Enigma\font.h"
#include <cmath>
#include <iostream>

enum STATUS {
    OFF = 0,
    ON = 1,
    WAIT = 2
};

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
    /*text.setOrigin(Button.getPosition().x, Button.getPosition().y);*/
    text.setPosition(float(position.x)-(Button.getOrigin().x/2.f), float(position.y) - (Button.getOrigin().y/2.f));
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
    /*text.setOrigin(Button.getPosition().x, Button.getPosition().y);*/
    text.setPosition(float(position.x) - (Button.getOrigin().x / 2.f), float(position.y) - (Button.getOrigin().y / 2.f));
    text.setStyle(sf::Text::Bold);
    // status
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
    /*text.setOrigin(Button.getPosition().x, Button.getPosition().y); */

    text.setPosition(100.f - (Button.getOrigin().x / 2.f), 150.f - (Button.getOrigin().y / 2.f));
    text.setStyle(sf::Text::Bold);
};

void button::setpos(int x, int y) {

    Button.setPosition(sf::Vector2f(float(x), float(y)));
    text.setPosition(float(x) - (Button.getOrigin().x / 2.f), float(y) - (Button.getOrigin().y / 2.f));
};

void button::setscale(int x, int y) {

    Button.setSize(sf::Vector2f(float(x), float(y)));
    Button.setOrigin(float(x / 2), float(y / 2));
    text.setCharacterSize(unsigned int(20));
    //text.setOrigin(float(x/2), float(y/2));
    
    
};

void button::settext(std::string Text) {

    textstr.str("");
    textstr << Text;
    text.setString(textstr.str());
};

void button::setColour(int r, int g, int b, int whatColour) {
    switch (whatColour) {
    case 1:
        mainColour[0] = r;          // 90 90 90 
        mainColour[1] = g;
        mainColour[2] = b;
        Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
    case 2:
        secColour[0] = r;           // 150 150 150 
        secColour[1] = g;
        secColour[2] = b;
        Button.setOutlineColor(sf::Color(secColour[0], secColour[1], secColour[2]));
    case 3:
        selColour[0] = r;           // 255, 120, 30
        selColour[1] = g;
        selColour[2] = b;
    }
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


short int button::pressed1(short int status) {
    
    if ((abs(Button.getPosition().x - float((sf::Mouse::getPosition()).x))) < Button.getSize().x /2.f){
        if ((abs(Button.getPosition().y - float((sf::Mouse::getPosition()).y))) < Button.getSize().y /2.f) {
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
    }
    return status;
    

};
short int button::pressed2(short int status, sf::Event event) {
    if ((abs(Button.getPosition().x - float((sf::Mouse::getPosition()).x))) < Button.getSize().x / 2.f) {
        if ((abs(Button.getPosition().y - float((sf::Mouse::getPosition()).y))) < Button.getSize().y / 2.f) {
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
    }
    return STATUS::OFF;


};
short int button::pressed3(short int status, sf::RenderWindow& window) {
    if (abs(Button.getPosition().x - float(sf::Mouse::getPosition(window).x)) < Button.getSize().x / 2.f) {
        if (abs(Button.getPosition().y - float(sf::Mouse::getPosition(window).y)) < Button.getSize().y / 2.f) {
            Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));

            /*std::cout << Button.getPosition().y << std::endl;             // checks positions of mouse and button
            std::cout << window.getPosition().y << std::endl;
            std::cout << sf::Mouse::getPosition().y << std::endl;
            std::cout << float(sf::Mouse::getPosition().y - window.getPosition().y) << std::endl;
            std::cout << Button.getOrigin().y << std::endl;
            std::cout << Button.getSize().y << std::endl;*/

            if (status == STATUS::ON) {
                Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                status = STATUS::OFF;
                return status;
            }
            status = STATUS::ON;
            return status;

        }
    }
    return status;


};

short int button::pressed4(short int status,sf::Vector2i buttonpos, sf::RenderWindow& window) {
    if (abs(float(buttonpos.x)- float(sf::Mouse::getPosition(window).x)) < Button.getSize().x / 2.f) {
        if (abs(float(buttonpos.y) - float(sf::Mouse::getPosition(window).y)) < Button.getSize().y / 2.f) {
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

short int button::pressed(short int status, bool mode, sf::RenderWindow& window) {
    if (abs(Button.getPosition().x - float(sf::Mouse::getPosition(window).x)) < Button.getSize().x / 2.f) {
        if (abs(Button.getPosition().y - float(sf::Mouse::getPosition(window).y)) < Button.getSize().y / 2.f) {
            Button.setFillColor(sf::Color(selColour[0], selColour[1], selColour[2]));

            /*std::cout << Button.getPosition().y << std::endl;             // checks positions of mouse and button
            std::cout << window.getPosition().y << std::endl;
            std::cout << sf::Mouse::getPosition().y << std::endl;
            std::cout << float(sf::Mouse::getPosition().y - window.getPosition().y) << std::endl;
            std::cout << Button.getOrigin().y << std::endl;
            std::cout << Button.getSize().y << std::endl;*/
            if (mode == true) {
                if (status == STATUS::ON) {
                    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                    status = STATUS::OFF;
                    return status;
                }
                status = STATUS::ON;
                return status;
            }
            else {
                if (status == STATUS::WAIT) {
                    Button.setFillColor(sf::Color(mainColour[0], mainColour[1], mainColour[2]));
                    return status;
                }
                status = STATUS::ON;
                return status;
            }

        }
    }
    return status;


};

