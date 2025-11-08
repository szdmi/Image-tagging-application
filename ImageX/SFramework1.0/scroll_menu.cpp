#include "scroll_menu.h"
#include <cmath>
#include <iostream>
#include "../Tester.h"





scroll_menu::scroll_menu() {

	item_count = new Item;
	textList = new std::string;
};

scroll_menu::~scroll_menu() {

	delete[] item_count;
	delete[] textList;

}

scroll_menu::scroll_menu(short int number, sf::Vector2i menuSize, sf::Vector2i position, bool dropdown) {

	Tester::act_testing(false);

	startpos.x = 0;
	startpos.y = itemSize.y / 2;
	itempos = startpos;

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
		dropButton.setScale(Size.x, itemSize.y);
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

	numberOfItems = number;

	if (item_count != nullptr) {
		delete[] item_count;
		item_count = nullptr;
	}
	if (textList != nullptr) {
		delete[] textList;
		textList = nullptr;
	}

	firstLastItem.x = 0;

	if (numberOfItems > 0) {
		Tester::act_testing(false);
		Tester::print("generating arrays");
		item_count = new Item[numberOfItems];
		textList = new std::string[numberOfItems];

		Tester::print("setting up mover");

		moverSize = pow(Size.y, 2) / (numberOfItems * itemSize.y);
		moverPos = moverSize / 2;

		mover.setScale(20, moverSize);
		mover.setPosition(Position.x + menuSize.x - mover.getSize().x / 2, Position.y + moverPos);
		if (mover.getText() != "|") {
			mover.setText("|");
		}

		moverWay.setScale(sf::Vector2i(mover.getSize().x, Size.y));
		moverWay.setPosition(sf::Vector2i(Position.x + menuSize.x - mover.getSize().x / 2, Position.y + Size.y / 2));

		Tester::print("calculating scrollPos");

		scrollPos = short int((float(moverPos) / float(Size.y)) * float(numberOfItems * itemSize.y));

		Tester::print("begin counting the curNumOfItems");

		upperBorder = moverSize / 2;
		lowerBorder = Size.y - moverSize / 2;
		short int i = 0;
		std::string t;
		do {

			item_count[i].setPosition(sf::Vector2i(itempos.x + Position.x, itempos.y + Position.y));
			item_count[i].setSize(sf::Vector2i(Size.x - mover.getSize().x - indent, itemSize.y));

			itempos.y += distance;
			i++;

		} while (itempos.y <= (Size.y - itemSize.y / 2) && i != numberOfItems);

		curNumOfItems = i;
		itempos = startpos;
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
		item_count->setColour(r, g, b, 1);
	case 5:
		item_count->setColour(r, g, b, 3);
	case 6:
		moverWay.setColor(r, g, b);
	}
};


void scroll_menu::show(sf::RenderWindow& window) {

	if (dropdown == true) {
		dropButton.show(window);
	}
	if (selected == true) {

		if (numberOfItems > Size.y / 30) {
			moverWay.show(window);
			mover.show(window);
		}

		if (numberOfItems > 0) {
			for (short int i = firstLastItem.x; i < firstLastItem.x + curNumOfItems; i++) {

				if (i > numberOfItems) {
					Tester::print("Alert! Out of array!  i > max  1");
					window.close();
				}
				else if (i < 0) {
					Tester::print("Alert! Out of array!  i < 0    1");
					window.close();
				}
				else if (item_count[i].getPosition().y > (0 + Position.y) && item_count[i].getPosition().y < (Size.y + Position.y)) {
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
					item_count[i].setSize(sf::Vector2i(Size.x - mover.getSize().x - indent, itemSize.y));
					item_count[i].setText(t, window);
					item_count[i].show(window, true);
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
		scrollPos = short int((float(moverPos - Position.y) / float(moverWayLength)) * (numberOfItems * 30));
		int i = 1;
		while (i * distance <= scrollPos - Size.y / 2) {				// here would be more usefull at least binary search
			i += 1;
		}
		firstLastItem.x = i - 1;
	}
	else if (y > Position.y + lowerBorder) {
		moverPos = lowerBorder;
		mover.setPosition(Position.x + Size.x - mover.getSize().x / 2, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfItems * 30));
		firstLastItem.x = numberOfItems - curNumOfItems;
	}
	else {
		moverPos = upperBorder;
		mover.setPosition(Position.x + Size.x - mover.getSize().x / 2, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfItems * 30));
		firstLastItem.x = 0;
	}

	for (short int i = firstLastItem.x; i < firstLastItem.x + curNumOfItems; i++) {


		if (i > numberOfItems) {
			Tester::print("Alert! Out of array!  i > max   2");
			break;
		}
		else if (i < 0) {
			Tester::print("Alert! Out of array!  i < 0   2");
		}
		else {
			item_count[i].setPosition(sf::Vector2i(itempos.x + Position.x, itempos.y + Position.y));
			itempos.y += distance;
		}
	}

	itempos = startpos;
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

		if (mover_status == STATUS::ON && numberOfItems * distance > Size.y) {

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
			for (short int i = firstLastItem.x; (i < firstLastItem.x + curNumOfItems) && item_count != nullptr; i++) {
				mover_status = item_count[i].pressed3(0, window);								// ask which item have the cursor in his bounds

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