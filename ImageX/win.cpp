#include "win.h"
#include <fstream>
#include <iostream>
#include "C:\Users\slava\source\repos\ImageX\ImageX\SFramework1.0\fonts\font.h"
#include "C:\Users\slava\source\Laboratory\Испытательная\Испытательная\fmgr.h"

win::win() {
	//Window.close();
	this->winsize = sf::Vector2i(500, 500);
	Window.create(sf::VideoMode(winsize.x, winsize.y), "addition", sf::Style::Default);
	//setFont("-");
	font = loadFont(font);
	text.setFont(font);

}

win::win(sf::Vector2i winsize, std::string textbox) {
	//Window.close();
	this->winsize = winsize;
	Window.create(sf::VideoMode(winsize.x, winsize.y), "addition", sf::Style::Default);
	//setFont("-");
	font = loadFont(font);
	text.setFont(font);
	textstr << textbox;
	text.setString(textstr.str());
}
/*
short int win::winprocess() {

	short int foldernum = 0;
	bool pressed = false;

	launch();
	open(0);
	scroll_menu menu(getcounter(), winsize, sf::Vector2i(winsize.x/2, winsize.y / 2), false);

	for (int i = 0; i < getcounter(); i++) {
		menu.setTxt(i, getcount(i));
	}

	std::string tbuffer = "Apply";
	button add(sf::Vector2i(240, 40), sf::Vector2i(winsize.x*3/4, winsize.y - 25), Window, tbuffer);
	tbuffer = "Cancel";
	button cancel(sf::Vector2i(240, 40), sf::Vector2i(winsize.x/4, winsize.y - 25), Window, tbuffer);

	short int add_img = 0;
	short int cancel_sel = 0;
	short int tmp = -1;
	short int imgcount = 0;
	
	while (Window.isOpen()) {
		sf::Event evnt;


		while (Window.pollEvent(evnt)) {
			winclear();

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
				Window.close();
				return 0;
			}
			else if (add_img == 1 || sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
				std::cout << "Image selected: " << tmp << " <<" << std::endl;
				return tmp;
				Window.close();
			}
			else if(cancel_sel == 1 || sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
				return -1;
				Window.close();
			}
			else {

				if (evnt.type == sf::Event::MouseButtonPressed) {

					std::cout << "button pressed" << std::endl;

					add_img = add.pressed3(add_img,Window);
					cancel_sel = cancel.pressed3(cancel_sel, Window);

					if (menu.pressed(sf::Mouse::getPosition(Window).y, evnt, Window) >= 0) {
						tmp = menu.pressed(sf::Mouse::getPosition(Window).y, evnt, Window);
					}
					else {
						menu.pressed(sf::Mouse::getPosition(Window).y, evnt, Window);
					}

					menu.show(Window);
					add.show(Window);
					cancel.show(Window);

					status = 1;
				}
				else if (evnt.type == sf::Event::MouseMoved) {
					if (status == 1) {
						menu.pressed(sf::Mouse::getPosition(Window).y, evnt, Window);
						menu.show(Window);
						std::cout << "button moved" << std::endl;
					}
				}
				else if(evnt.type == sf::Event::MouseButtonReleased){
					std::cout << "button released" << std::endl;
					menu.pressed(sf::Mouse::getPosition(Window).y, evnt, Window);
					menu.show(Window);
					status = 0;
				}

				
				if (tmp >= 0) {
					
						open(tmp);
					
					menu.update(getcounter(), winsize, sf::Vector2i(winsize.x / 2, winsize.y / 2));
					std::cout << "folder opened" << std::endl;
					for (int i = 0; i < getcounter(); i++) {
						menu.setTxt(i, getcount(i));
					}
					images[imgcount];
					imgcount += 1;
					tmp = -1;

				}
				menu.show(Window);
				add.show(Window);
				cancel.show(Window);
				Window.display();
			}
		}
	}

	return 0;
}
*/