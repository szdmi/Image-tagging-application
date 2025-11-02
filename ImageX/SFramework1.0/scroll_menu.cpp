#include "scroll_menu.h"
#include <cmath>
#include <iostream>
#include "../Tester.h"




scroll_menu::scroll_menu() {

	tagcount = new tag;
	textList = new std::string;
};

scroll_menu::~scroll_menu() {

	delete[] tagcount;
	delete[] textList;

}

scroll_menu::scroll_menu(short int number, sf::Vector2i menuSize, sf::Vector2i position, bool dropdown) {

	Tester::act_testing(false);

	startpos.x = 0;
	startpos.y = tagSize.y / 2;
	tagpos = startpos;

	if (dropdown == false) {

		update(number, menuSize, position);
		selected = true;
	}
	else {
		this->dropdown = true;
		dropButton.setText("Select");
		dropButton.setColour(90, 90, 90, 1);
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
		dropButton.setPosition(position.x, position.y);
		Position.y = position.y + dropButton.getSize().y / 2 + indent;
		Position.x = position.x - Size.x / 2;
	}
	else {
		Position.x = position.x - Size.x / 2;
		Position.y = position.y - Size.y / 2;
	}
};

void scroll_menu::setScale(sf::Vector2i menuSize) {

	Size = menuSize;

	if (dropdown == true) {
		dropButton.setScale(Size.x, tagSize.y);
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

	if (tagcount != nullptr) {
		delete[] tagcount;
		tagcount = nullptr;
	}
	if (textList != nullptr) {
		delete[] textList;
		textList = nullptr;
	}

	firstLastTag.x = 0;

	if (numberOfTags > 0) {
		Tester::act_testing(false);
		Tester::print("generating arrays");
		tagcount = new tag[numberOfTags];
		textList = new std::string[numberOfTags];

		Tester::print("setting up mover");

		moverSize = pow(Size.y, 2) / (numberOfTags * tagSize.y);
		moverPos = moverSize / 2;

		mover.setScale(20, moverSize);
		mover.setPosition(Position.x + menuSize.x - mover.getSize().x / 2, Position.y + moverPos);
		if (mover.getText() != "|") {
			mover.setText("|");
		}

		moverWay.setScale(sf::Vector2i(mover.getSize().x, Size.y));
		moverWay.setPosition(sf::Vector2i(Position.x + menuSize.x - mover.getSize().x / 2, Position.y + Size.y / 2));

		Tester::print("calculating scrollPos");

		scrollPos = short int((float(moverPos) / float(Size.y)) * float(numberOfTags * tagSize.y));

		Tester::print("begin counting the curNumOfTags");

		upperBorder = moverSize / 2;
		lowerBorder = Size.y - moverSize / 2;
		short int i = 0;
		std::string t;
		do {

			tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x, tagpos.y + Position.y));
			tagcount[i].setSize(sf::Vector2i(Size.x - mover.getSize().x - indent, tagSize.y));

			tagpos.y += distance;
			i++;

		} while (tagpos.y <= (Size.y - tagSize.y / 2) && i != numberOfTags);

		curNumOfTags = i;
		tagpos = startpos;
		Tester::print("counted");
		Tester::act_testing(false);
	}
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

		if (numberOfTags > Size.y / 30) {
			moverWay.show(window);
			mover.show(window);
		}

		if (numberOfTags > 0) {
			for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {

				if (i > numberOfTags) {
					Tester::print("Alert! Out of array!  i > max  1");
					window.close();
				}
				else if (i < 0) {
					Tester::print("Alert! Out of array!  i < 0    1");
					window.close();
				}
				else if (tagcount[i].getPosition().y > (0 + Position.y) && tagcount[i].getPosition().y < (Size.y + Position.y)) {
					std::string t;
					t = textList[i];
					int maxlength = int((Size.x - mover.getSize().x - indent) / 15 /* - serves to cut length of text like : "Some_colou....png"*/);
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
					tagcount[i].setSize(sf::Vector2i(Size.x - mover.getSize().x - indent, tagSize.y));
					tagcount[i].setText(t, window);
					tagcount[i].showIgnore(1);
					tagcount[i].show(window, true);
				}
				else {

					continue;
				}
			}
		}
	}
};

short int scroll_menu::move(short int y, short int moverWayLength) {

	if (y <= Position.y + lowerBorder && y >= Position.y + upperBorder) {
		moverPos = y;
		mover.setPosition(Position.x + Size.x - mover.getSize().x / 2, moverPos);
		scrollPos = short int((float(moverPos - Position.y) / float(moverWayLength)) * (numberOfTags * 30));
		int i = 1;
		while (i * distance <= scrollPos - Size.y / 2) {				// here would be more usefull at least binary search
			i += 1;
		}
		firstLastTag.x = i - 1;
	}
	else if (y > Position.y + lowerBorder) {
		moverPos = lowerBorder;
		mover.setPosition(Position.x + Size.x - mover.getSize().x / 2, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfTags * 30));
		firstLastTag.x = numberOfTags - curNumOfTags;
	}
	else {
		moverPos = upperBorder;
		mover.setPosition(Position.x + Size.x - mover.getSize().x / 2, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfTags * 30));
		firstLastTag.x = 0;
	}

	for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {


		if (i > numberOfTags) {
			Tester::print("Alert! Out of array!  i > max   2");
			break;
		}
		else if (i < 0) {
			Tester::print("Alert! Out of array!  i < 0   2");
		}
		else {
			tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x, tagpos.y + Position.y));
			tagpos.y += distance;
		}
	}

	tagpos = startpos;
	return 0;
};

short int scroll_menu::pressed(short int y, sf::Event event, sf::RenderWindow& window) {

	//							- dropdown mode - 
	if (dropdown == true) {
		drop_status = dropButton.pressed(drop_status, event, window, true);

		if (drop_status == STATUS::ON) {
			selected = true;
		}
		else {
			selected = false;
		}

	}
	// ----------------------------------------------------------------------------


	if (selected == true) {

		//								 - if cursor is out of menu bounds - 

		if (!(abs(float(Position.y) + (Size.y / 2) - float(sf::Mouse::getPosition(window).y)) < (Size.y / 2)) && event.type == sf::Event::MouseButtonPressed) {
			return NOTHING_SELECTED;
		}

		moverPos = y;					// 

		//								- if cursor is in X bounds of mover  - 

		if ((event.type == sf::Event::MouseButtonPressed && mover.pressed4(0, sf::Vector2f(Size.x - mover.getSize().x / 2 + Position.x, moverPos), window) == STATUS::ON) || mover_status == STATUS::ON) {

			mover_status = STATUS::ON;
			mouseLeftPressed = true;
			Tester::print("cursor is in X bounds of mover");
		}
		//								- if its not -
		else {
			mover_status = STATUS::OFF;
		}

		//								- if cursor is in bounds of mover_way and number of elements is greater than the size of menu box - 

		if (mover_status == STATUS::ON && numberOfTags * distance > Size.y) {

			switch (event.type) {
			case sf::Event::MouseButtonReleased:

				mouseLeftPressed = false;
				mover.changeColor(false);
				mover_status = STATUS::OFF;
				Tester::print("MouseButtonReleased");
				break;

			case sf::Event::MouseButtonPressed:				// relocate to mouse cursor

				mover.changeColor(true);
				move(y, Size.y);
				Tester::print("MouseButtonPressed");
				break;

			case sf::Event::MouseMoved:						// move with a mmouse

				if (mouseLeftPressed == true) {
					move(y, Size.y);
				}
				Tester::print("MouseMoved");
				break;
			}

			return MOVER_MOVED;
		}

		//								- if action was not performed with the mover -

		else if (mover_status != STATUS::ON) {

			Tester::print(" - NON mover action");
			for (short int i = firstLastTag.x; (i < firstLastTag.x + curNumOfTags) && tagcount != nullptr; i++) {
				mover_status = tagcount[i].pressed3(0, window);								// ask which tag have the cursor in his bounds

				if (mover_status == STATUS::ON) {											// return state to normal
					mover_status = STATUS::OFF;
					return i;										// return index of the object in the array 
				}
			}
			return NOTHING_SELECTED;
		}

		return NOTHING_SELECTED;
	}
	return NOTHING_SELECTED;
};

void scroll_menu::setSelected(bool set) {
	selected = set;
	dropButton.changeColor(false);
	drop_status = STATUS::OFF;
};