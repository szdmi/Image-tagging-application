#include "scroll_menu.h"
#include <cmath>
#include <iostream>




scroll_menu::scroll_menu() {
	tagcount = new tag;
	textList = new std::string;
};

scroll_menu::~scroll_menu() {
	delete[] tagcount;
	delete[] textList;

}

scroll_menu::scroll_menu(short int number,sf::Vector2i menuSize, sf::Vector2i position, bool dropdown) {
	
	if (dropdown == false) {
		
		update(number, menuSize, position);
		selected = true;
	}
	else {
		this->dropdown = true;
		//dropButton.setScale(menuSize.x, 30);
		dropButton.setText("Select");
		dropButton.setColour(90,90,90,1);
		dropButton.setColour(120, 120, 120, 2);
		dropButton.setColour(120, 120, 120, 3);
		dropButton.setOutlineThickness(2);
		
		update(number, menuSize, position);
	}
	
	mover.setOutlineThickness(2);
};


void scroll_menu::setText(int n, std::string txt) {
	
	textList[n] = txt;
};

void scroll_menu::setPosition(sf::Vector2i position) {
	if (dropdown == true) {
		//Position = position;
		dropButton.setPosition(position.x, position.y);
		Position.y = position.y + 25;
		Position.x = position.x - Size.x / 2;
	}
	else {
		Position.x = position.x - Size.x/2;
		Position.y = position.y - Size.y/2;
	}
};

void scroll_menu::setScale(sf::Vector2i menuSize) {
	Size = menuSize;
	if (dropdown == true) {
		dropButton.setScale(Size.x, 20);
		//dropButton.setPosition(Position.x, Position.y);
		//Position.y += 25;
		//Position.x -= Size.x / 2;
	}
	else {
		Position.x = Position.x - Size.x / 2;
		Position.y = Position.y - Size.y / 2;
	}
};

void scroll_menu::update(short int number, sf::Vector2i menuSize, sf::Vector2i position) {
	if (dropdown == true) {
		//dropButton.setScale(menuSize.x, 30);
	}
	setScale(menuSize);
	setPosition(position);

	numberOfTags = number;

	if (tagcount != NULL) {
		delete[] tagcount;
	}
	if (textList != NULL) {
		delete[] textList;
	}

	firstLastTag.x = 0;

	tagcount = new tag[numberOfTags];
	textList = new std::string[numberOfTags];

	moverSize = pow(Size.y, 2) / (numberOfTags * 30);
	moverPos = moverSize / 2;

	mover.setScale(20, moverSize);
	mover.setPosition(Position.x + menuSize.x - 10, Position.y + moverPos);
	if (mover.getText() != "|") {
		mover.setText("|");
	}

	moverWay.setScale(sf::Vector2i(20, Size.y));
	moverWay.setPosition(sf::Vector2i(Position.x + menuSize.x - 10, Position.y + Size.y / 2));

	scrollPos = short int((float(moverPos) / float(Size.y)) * float(numberOfTags * 30));

	upperBorder = moverSize / 2;
	lowerBorder = Size.y - moverSize / 2;
	short int i = 0;
	std::string t;
	do {

		tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x + 2, tagpos.y + Position.y));
		tagcount[i].setTaglength(Size.x - 29);
		
		tagpos.y += distance;
		i++;

	} while (tagpos.y < Size.y && i != numberOfTags);

	curNumOfTags = i;
	tagpos = sf::Vector2i(0, 30);

};

void scroll_menu::setColour(int r, int g, int b, int whatColor) {
	switch (whatColor) {
	case 1:
		dropButton.setColour(r, g, b, 1);
		mover.setColour(r, g, b, 1);
	case 2:
		dropButton.setColour(r, g, b, 2);
		mover.setColour(r, g, b, 2);

	case 3:
		dropButton.setColour(r, g, b, 3);
		mover.setColour(r, g, b, 3);

	case 4:
		tagcount->setColour(r, g, b, 1);
	case 5:
		tagcount->setColour(r, g, b, 3);
	case 6:
		moverWay.setColor(r, g, b);
	}
};


void scroll_menu::show(sf::RenderWindow& window) {
	if (dropdown == true) {
		dropButton.show(window);
	}
	if (selected == true) {
		if (numberOfTags > Size.y/30) {
			moverWay.show(window);
			mover.show(window);									
		}


		for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {

			if (i > numberOfTags) {
				std::cout << "Alert! Out of array!  i > max  1" << std::endl;
				window.close();
			}
			else if (i < 0) {
				std::cout << "Alert! Out of array!  i < 0    1" << std::endl;
				window.close();
			}
			else if (tagcount[i].getPosition().y > (0 + Position.y) && tagcount[i].getPosition().y < (Size.y + Position.y)) {
				std::string t;
				/*t = std::to_string(i+1);
				tags[i].setTxt(t, window);*/
				t = textList[i];
				int maxlength = int((Size.x - 29) / 15);
				if (t.length() > maxlength) {
					std::string tmp;
					for (int i = 0; i < maxlength; i++) {
						tmp += t[i];
					}
					tmp += "...";
					for (int i = t.length() - 4; i < t.length(); i++) {
						tmp += t[i];
					}
					t = tmp;
				}
				tagcount[i].setTaglength(Size.x - 29);
				tagcount[i].setText(t, window);
				tagcount[i].showIgnore(1);
				tagcount[i].show(window, true);
			}
			else {

				continue;
			}
		}
	}
};

short int scroll_menu::move(short int y, short int moverWayLength) {
	
	if (y <= Position.y + lowerBorder && y >= Position.y + upperBorder) {
		moverPos = y;
		mover.setPosition(Position.x + Size.x - 10,  moverPos);
		scrollPos = short int((float(moverPos - Position.y) / float(moverWayLength)) * (numberOfTags * 30))/* - winsize.y / 2 + distance / 2*/;
		int i = 1;
		while(i*distance <= scrollPos - Size.y / 2) {				// here would be more usefull at least binary search
			i += 1;
		}
		firstLastTag.x = i-1;
	}
	else if (y > Position.y + lowerBorder) {
		moverPos = lowerBorder;
		mover.setPosition(Position.x + Size.x - 10, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfTags * 30));
		firstLastTag.x = numberOfTags - curNumOfTags;
	}
	else {
		moverPos = upperBorder;
		mover.setPosition(Position.x + Size.x - 10, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfTags * 30));
		firstLastTag.x = 0;
	}

	for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {


		if (i > numberOfTags) {
			std::cout << "Alert! Out of array!  i > max   2" << std::endl;
			break;
		}
		else if (i < 0) {
			std::cout << "Alert! Out of array!  i < 0   2" << std::endl;
		}
		else {
			tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x + 2, tagpos.y + Position.y));
			tagpos.y += distance;
		}
	}

	tagpos = sf::Vector2i(0, 30);
	return 0;
};

short int scroll_menu::pressed(short int y, sf::Event event, sf::RenderWindow &window) {
	
	if (dropdown == true ) {
		drop_status = dropButton.pressed(drop_status, event, window, true);
		if (drop_status == STATUS::ON) {
			selected = true;
		}
		else {
			selected = false;
		}
		
	}
	if (selected == true) {

		if (!(abs(float(Position.y) + (Size.y / 2) - float(sf::Mouse::getPosition(window).y)) < (Size.y / 2)) && event.type == sf::Event::MouseButtonPressed) {
			return NOTHING_SELECTED;
		}

		moverPos = y;

		if (event.type == sf::Event::MouseButtonPressed && mover.pressed4(0, sf::Vector2f(Size.x - 10 + Position.x, moverPos), window) == STATUS::ON || mover_status == STATUS::ON) {

			mover_status = STATUS::ON;
			mouseLeftPressed = true;
		}
		else {
			mover_status = STATUS::OFF;
		}

		if (mover_status == STATUS::ON && numberOfTags > 13) {		

			switch (event.type) {
			case sf::Event::MouseButtonReleased:

					mouseLeftPressed = false;
					mover.changeColor(false);
					mover_status = STATUS::OFF;
					break;

			case sf::Event::MouseButtonPressed:

				mover.changeColor(true);
				move(y, Size.y);
				break;

			case sf::Event::MouseMoved:
				if (mouseLeftPressed == true) {
					move(y, Size.y);
				}
				break;
			}

			return MOVER_MOVED;
		}
		else if (mover_status != STATUS::ON) {

			for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {
				mover_status = tagcount[i].pressed3(0, window);
				if (mover_status == STATUS::ON) {
					mover_status = STATUS::OFF;
					return i;										// return index of the object in the array 
				}
			}
			return NOTHING_SELECTED;
		}

		std::cout << mover_status << "--" << std::endl;

		return NOTHING_SELECTED;
	}
	return NOTHING_SELECTED;
};
