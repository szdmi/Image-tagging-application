#include "scroll_menu.h"
#include <cmath>
#include <iostream>
//#include "fmgr.h"

#define MBL 100
#define TAG_SIZE 30;
//tag* scroll_menu::gettag(int n);

scroll_menu::scroll_menu() {

};

scroll_menu::~scroll_menu() {
	delete[] tagcount;
	delete[] textList;

}

scroll_menu::scroll_menu(short int number,sf::Vector2i menuSize, sf::Vector2i position, bool dropdown) {
	
	if (dropdown == false) {
		
		general(number, menuSize, position);
		selected = true;
	}
	else {
		this->dropdown = true;
		selected_element.setscale(menuSize.x, 30);
		selected_element.settext("Select");
		
		general(number, menuSize, position);
		
		
		
	}
	
};

void scroll_menu::general(short int number, sf::Vector2i menuSize, sf::Vector2i position) {
	
													// positioning problem

	setPosition(position, menuSize);

	numberOfTags = number;
	winsize = sf::Vector2i(menuSize.x, menuSize.y);		// -60



	tagcount = new tag[numberOfTags];
	textList = new std::string[numberOfTags];
	

	moverSize = pow(winsize.y, 2) / (numberOfTags * 30);
	moverPos = moverSize / 2;
	mover.setscale(20, moverSize);
	mover.setpos(Position.x + menuSize.x - 10, Position.y + moverPos);
	mover.settext("|");
	moverWay.setScale(sf::Vector2i(20, winsize.y));
	moverWay.setPos(sf::Vector2i(Position.x + menuSize.x - 10, Position.y + winsize.y / 2));
	moverWay.setColor(150,150,150);

	scrollPos = short int((float(moverPos) / float(winsize.y)) * float(numberOfTags * 30));

	upperBorder = moverSize / 2;
	lowerBorder = winsize.y - moverSize / 2;
	short int i = 0;
	std::string t;

	do {
		tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x + 2, tagpos.y + Position.y));
		tagcount[i].setlength(winsize.x - 29);
		tagpos.y += distance;
		i++;

	} while (tagpos.y < winsize.y && i != numberOfTags);

	/*do{
		tags[i].setPosition(tagpos);

		t = std::to_string(i+1);
		tags[i].setTxt( t, window);

		tagpos.y += distance;
		i++;
	} while (tagpos.y < winsize.y);*/
	curNumOfTags = i;
	tagpos = sf::Vector2i(0, 30);
}

void scroll_menu::setTxt(int n, std::string txt) {
	
	textList[n] = txt;
};

void scroll_menu::setPosition(sf::Vector2i position, sf::Vector2i menuSize) {
	if (dropdown == true) {
		Position = position;
		selected_element.setpos(position.x, position.y);
		Position.y += 25;
		Position.x -= menuSize.x / 2;
	}
	else {
		Position.x = position.x - menuSize.x/2;
		Position.y = position.y - menuSize.y/2;
	}
};

void scroll_menu::update(short int number, sf::Vector2i menuSize, sf::Vector2i position) {
	if (dropdown == true) {
		selected_element.setscale(menuSize.x, 30);
	}
	
	setPosition(position, menuSize);

	numberOfTags = number;
	winsize = sf::Vector2i(menuSize.x, menuSize.y);				// -60
	delete[] tagcount;
	delete[] textList;
	firstLastTag.x = 0;

	tagcount = new tag[numberOfTags];
	textList = new std::string[numberOfTags];

	moverSize = pow(winsize.y, 2) / (numberOfTags * 30);
	moverPos = moverSize / 2;
	mover.setscale(20, moverSize);
	mover.setpos(Position.x + menuSize.x - 10, Position.y + moverPos);
	moverWay.setScale(sf::Vector2i(20, winsize.y));
	moverWay.setPos(sf::Vector2i(Position.x + menuSize.x - 10, Position.y + winsize.y / 2));

	scrollPos = short int((float(moverPos) / float(winsize.y)) * float(numberOfTags * 30));

	upperBorder = moverSize / 2;
	lowerBorder = winsize.y - moverSize / 2;
	short int i = 0;
	std::string t;
	do {

		tagcount[i].setPosition(sf::Vector2i(tagpos.x + Position.x + 2, tagpos.y + Position.y));
		tagcount[i].setlength(winsize.x - 29);
		tagpos.y += distance;
		i++;

	} while (tagpos.y < winsize.y && i != numberOfTags);

	curNumOfTags = i;
	tagpos = sf::Vector2i(0, 30);

};

void scroll_menu::setColour(int r, int g, int b, int whatColor) {
	switch (whatColor) {
	case 1:
		selected_element.setColour(r, g, b, 1);
		mover.setColour(r, g, b, 1);
	case 2:
		selected_element.setColour(r, g, b, 2);
		mover.setColour(r, g, b, 2);

	case 3:
		selected_element.setColour(r, g, b, 3);
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
		selected_element.show(window);
	}
	if (selected == true) {
		if (numberOfTags > winsize.y/30) {
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
			else if (tagcount[i].getPosition().y > (0 + Position.y) && tagcount[i].getPosition().y < (winsize.y + Position.y)) {
				std::string t;
				/*t = std::to_string(i+1);
				tags[i].setTxt(t, window);*/
				t = textList[i];
				int maxlength = int((winsize.x - 29) / 15);
				if (t.length() > maxlength) {
					std::string tmp;
					for (int i = 0; i < maxlength; i++) {
						tmp += t[i];
					}
					tmp += "...";
					for (int i = t.length() - 3; i < t.length(); i++) {
						tmp += t[i];
					}
					t = tmp;
				}
				tagcount[i].setlength(winsize.x - 29);
				tagcount[i].setTxt(t, window);
				tagcount[i].tagshow(1);
				tagcount[i].show2(window);
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
		mover.setpos(Position.x + winsize.x - 10,  moverPos);
		scrollPos = short int((float(moverPos - Position.y) / float(moverWayLength)) * (numberOfTags * 30))/* - winsize.y / 2 + distance / 2*/;
		int i = 1;
		while(i*distance <= scrollPos - winsize.y / 2) {				// here would be more usefull at least binary search
			i += 1;
		}
		firstLastTag.x = i-1;
	}
	else if (y > Position.y + lowerBorder) {
		moverPos = lowerBorder;
		mover.setpos(Position.x + winsize.x - 10, Position.y + moverPos);
		scrollPos = short int((float(moverPos) / float(moverWayLength)) * (numberOfTags * 30));
		firstLastTag.x = numberOfTags - curNumOfTags;
	}
	else {
		moverPos = upperBorder;
		mover.setpos(Position.x + winsize.x - 10, Position.y + moverPos);
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
			//firstLastTag.x = +scrollPos;
			tagpos.y += distance;
		}
	}

	tagpos = sf::Vector2i(0, 30);
	return 0;
};

short int scroll_menu::pressed(short int y, sf::Event mouse, sf::RenderWindow &window) {
	if (dropdown == true) {
		status2 = selected_element.pressed(status2, true ,window);
		if (status2 == STATUS::ON) {
			selected = true;
			
		}
		else {
			selected = false;
		}
		
	}
	if (selected == true) {
		moverPos = y;

		if (mover.pressed4(0, sf::Vector2i(winsize.x - 10 + Position.x, moverPos), window) == 1 || status == 1) {
			status = STATUS::ON;
			//std::cout << "status 1" << std::endl;
		}
		else {
			status = STATUS::OFF;
			//std::cout << "status 0" << std::endl;
		}
		//std::cout << "Wrong signal 1 " << moverPos << " " << std::endl;

		if (status == STATUS::ON && numberOfTags > 13) {

			short int instat = STATUS::OFF;     // it make the release event working properly

			switch (mouse.type) {
			case sf::Event::MouseButtonReleased:

				if (instat != STATUS::WAIT) {
					mover.changeColor(false);
					//std::cout << "Wrong signal 2 " << std::endl;
					status = STATUS::OFF;
				}

			case sf::Event::MouseButtonPressed:

				//std::cout << "Wrong signal 1 " << std::endl;
				instat = STATUS::WAIT;
				move(y, winsize.y);

			case sf::Event::MouseMoved:

				move(y, winsize.y);

			}

			return MOVER_MOVED;
		}
		else if (status != STATUS::ON) {

			for (short int i = firstLastTag.x; i < firstLastTag.x + curNumOfTags; i++) {
				status = tagcount[i].pressed3(0, window);
				if (status == STATUS::ON) {
					//std::cout << "index i was " << i << std::endl;
					status = STATUS::OFF;
					return i;										// return index of the folder in array 'folders'
				}
			}
			return NOTHING_SELECTED;
		}

		std::cout << status << "--" << std::endl;

		return NOTHING_SELECTED;
	}
	return NOTHING_SELECTED;
};
