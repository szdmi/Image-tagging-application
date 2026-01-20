#include <math.h>
#include "SFramework1.0\icon.h"
#include "SFramework1.0\tag.h"
#include "SFramework1.0\scroll_menu.h"
#include "fmgr.h"
#include "text_field.h"
//#include "win.h"



//#define DEB      // debug mode



namespace var {

	// "pressed" variables (flags)

	short int exit = 0;
	short int addTag = 0;
	short int delTag = 0;
	short int removeTag = -1;
	short int changeMod = 0;
	short int setPath = 0;
	short int watchMode = 0;
	short int addReplace = 0;
	short int applyTo = 0;
	short int search = 0;
	short int assign = 0;

	// "selected" variables 

	short int search_select = -1;
	short int assign_select = -1;

	std::string imgname = "image name.jpg";
	std::string resolution = "1920 x 1080";

	bool shortview = false;                                             // no button`s are active ( except of chosen one and the exit button ) while this variable is true

	// counts

	tag* tags;                                                          // tags array pointer
	int tagcount = 0;
	int search_results = 1;
	int assign_results = 1;

	int curTag = 0;
	sf::Vector2i startpoint(550, 880);                                  // first tag position
	sf::Vector2i indent = sf::Vector2i(20, 40);
	sf::Vector2i tagPos = startpoint;                                // position of the last tag


	sf::Texture texture;                                                // for image(texture/sprite) loading
	sf::Image image;
	sf::Sprite sprite;
	std::string curFolder;
	short int selected = -1;
	sf::RectangleShape imageborder;
	bool fullscreen = false;

	// icons

	sf::Image fail_image;



}



static tag* tagsNumberChanged(short int n, bool add_or_delete) {

	if (add_or_delete == true) {                                        // true == add         false == delete     
		n = var::tagcount;                                              // n - place in array to insert a new tag ( at the end by default )
		tag* p = NULL;
		var::tagcount += 1;
		p = new tag[var::tagcount];                                     // creating new array of tags
		if (var::tags != NULL) {
			for (int i = 0; i < var::tagcount; i++) {
				if (i > n) {
					p[i] = var::tags[i - 1];
				}
				else if (i == n) {
					//p[i] = var::curTag;   
					////////////////////////////////////
					//p[i] = var::tags[i];
					//p[i + 1] = var::tags[i];
				}
				else {
					p[i] = var::tags[i];
				}
			}
			delete[] var::tags;                                             // deleting old array
		}
		return p;
	}
	else {
		tag* p = NULL;
		if (var::tagcount > 1) {
			var::tagcount -= 1;
			p = new tag[var::tagcount];                                     //creating new array
			for (int i = 0; i < var::tagcount; i++) {
				if (i > n) {
					p[i - 1] = var::tags[i];
				}
				else if (i == n) {
					var::tags[i].deleteTag();
				}
				else {
					p[i] = var::tags[i];
				}
			}
			delete[] var::tags;                                             // deleting the old one
		}
		return p;
	}


}

float sprite_resize(sf::Vector2i field) {
	sf::Vector2u texture_size = var::texture.getSize();
	float resize = 0.f;


	if (float(texture_size.x) / field.x > float(texture_size.y) / field.y) {
		resize = float(texture_size.x) / field.x;
	}
	else {
		resize = float(texture_size.y) / field.y;
	}

	return resize;
}

void imageLoad(std::string path, sf::Vector2i field) {

	if (var::image.loadFromFile(path) == false) {
		var::imgname = "ERROR WHILE LOADING image";
	}

	if (var::texture.loadFromImage(var::image) == false) {
		var::imgname = "ERROR WHILE LOADING texture";
		var::texture.loadFromImage(var::fail_image);

	}
	else {
		var::sprite.setTexture(var::texture, true);
	}

	float resize = sprite_resize(field);

	var::sprite.setScale(sf::Vector2f(1.f / resize, 1.f / resize));
	var::sprite.setPosition(sf::Vector2f(960.f - var::texture.getSize().x / (2 * resize), 490.f - var::texture.getSize().y / (2 * resize)));

};



int main() {

	// ------------------ initialize components ---------------------

	
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080), "ImageX", sf::Style::Close);							// creating main window

	/*unsigned int menuStatus1 = 0;
	unsigned int searchStatus = 0;*/

	std::string textbuffer;
	std::string search_results[100];

	var::tags = new tag[1];                                                                         // array of tags of the image
	var::tagcount = 1;                                                                              // tagcount must be always bigger than 0, because of addTag function 


	// ======================= loading fonts ======================
	tag::loadTagFont();
	button::loadButtonFont();
	Item::loadItemFont();

	// ====================== loading images ========================

	var::fail_image.loadFromFile("C:/Users/slava/source/repos/ImageX/icons/broken-image.png");

	// ==================== file manager initialization ==================
	launch();
	open(0);
	setfilter(".jpg");
	setfilter(".jpeg");
	setfilter(".png");

	scroll_menu menu(getcounter(), sf::Vector2i(300, 600), sf::Vector2i(1700, 540), false);

	scroll_menu search_menu(15/*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 310), false);

	scroll_menu assign_menu(1000/*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 710), false);



	search_menu.setColour(150, 150, 150, 2);
	assign_menu.setColour(150, 150, 150, 2);

	for (int i = 0; i < getcounter(); i++) {
		menu.setText(i, getcount(i));
	}

	for (int i = 0; i < 1000; i++) {
		assign_menu.setText(i, std::to_string(i));

	}


	// ====== Exit button =======
	char exit[12] = "Exit";
	button Exit = button(sf::Vector2i(100, 40), sf::Vector2i(60, 30), window, exit);


	//====== change mod button ======
	char mod[12] = "watch";
	button Mod(sf::Vector2i(300, 40), sf::Vector2i(250, 30), window, mod);

	//====== Add tag button ======
	char add[] = "Add tag";
	button Add(sf::Vector2i(200, 40), sf::Vector2i(140, 900), window, add);


	//====== Delete tag button ======
	char del[12] = "Del tag";
	button Del(sf::Vector2i(200, 40), sf::Vector2i(340, 900), window, del);

	//====== Add/Replace tags ======
	button add_replace(sf::Vector2i(100, 30), sf::Vector2i(290, 595), window, "A/R");
	add_replace.setOutlineThickness(0);
	add_replace.setColour(100, 100, 100, 1);

	//====== Apply tags to Single/Multiple images ======
	button apply_to(sf::Vector2i(100, 30), sf::Vector2i(390, 595), window, "S/M");
	apply_to.setOutlineThickness(0);
	apply_to.setColour(100, 100, 100, 1);

	//====== Folder list field ======

	field FolderField(sf::Vector2i(300, 600), sf::Vector2i(1700, 540), window);

	//====== Image field ======
	field ImageField(sf::Vector2i(960, 850), sf::Vector2i(960, 570), window);

	//====== List field ======
	field ListField(sf::Vector2i(410, 680), sf::Vector2i(240, 520), window);


	//====== Image Icon ======

	icon ImgInfo(sf::Vector2i(960, 100), sf::Vector2i(960, 140), window, var::imgname, var::resolution);

	//====== Tags Icon ======
	std::string tagicon = "Image tags:";
	icon Tagicon(sf::Vector2i(960, 30), sf::Vector2i(960, 840), window, tagicon);

	//====== Text bars ======
	text_field search_bar(sf::Vector2i(410, 30), sf::Vector2i(240, 195));
	search_bar.setColor(100, 100, 100);

	text_field assign_bar(sf::Vector2i(210, 30), sf::Vector2i(140, 595));
	assign_bar.setColor(100, 100, 100);

	text_field folder_path(sf::Vector2i(300, 40), sf::Vector2i(1700, 200));
	folder_path.setColor(100, 100, 100);

	// ------------------------------ begin of main loop ---------------------------

	while (window.isOpen()) {
		sf::Event event;
		sf::Vector2i mousepos = sf::Mouse::getPosition(window);                                     // current mouse position 

		while (window.pollEvent(event)) {                                                            // main event loop


			window.clear(sf::Color(0, 0, 0));



			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {                                 // close the program
				window.close();
				break;
			}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {                                      // debug stuff
			//    if (var::shortview == false) {
			//        var::addTag = 1;
			//    }
			//}
			//if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {                                      // debug stuff
			//    if (var::shortview == false) {
			//        var::delTag = 1;
			//    }
			//}

			// ======================= Custom events ==========================

			if (var::exit == 1) {                                                                   // close the program
				window.close();
				break;
			} 

			if (var::addTag == 1) {                                                                 // adding new tag to tags array
				var::shortview = true;

				if (var::curTag > 14) {                                                             // some checks
					//window.close();
					std::cout << "Max number of tags reached!" << var::curTag << std::endl;
					var::shortview = false;
					var::addTag = 0;
				}

				else if (var::curTag < 0 || var::curTag > 14) {
					std::cout << "curTag alert! " << var::curTag << std::endl;
					var::shortview = false;
					window.close();
				}

				else {
					/////////////////////////////////

					var::tags[var::curTag].setSelected(true);                                               // set on selection of the tag (planned, but not currently in use )
					var::tags[var::curTag].showIgnore(1);                                                   // allowing the tag to display (only for static array usage)
					var::tags[var::curTag].setPosition(sf::Vector2i(var::tagPos.x, var::tagPos.y));   // setting tag`s position
					switch (event.type) {
					case sf::Event::TextEntered:
						var::addTag = var::tags[var::curTag].typedOn(event);                                // function that writes name of the tag

					}
					var::tags[var::curTag].show(window, false);

					///////////////////////////////

					if (var::addTag == 0) {
						try {
							var::tags = tagsNumberChanged(var::curTag, true);                                   // expanding tags array at 1
							//std::cout << var::tags[var::curTag].getPosition().x << "<<<<<<" << std::endl;        // 
							if ((var::curTag + 1) % 5 == 0) {                                                   // calculating future tag`s position
								var::curTag += 1;
								var::tagPos.x = var::startpoint.x;
								var::tagPos.y += var::indent.y;
								var::shortview = false;
							}
							else {
								var::tagPos.x = var::tags[var::curTag].getPosition().x + int(var::tags[var::curTag].getSize().x) + var::indent.x;
								var::curTag += 1;
								var::shortview = false;
							}
						}
						catch (const std::exception ex) {
							std::cout << " Warning! Malfunction detected! " << std::endl;
							window.close();
						}

					}
				}

				//var::shortview = false;
			}

			if (var::delTag == 1) {                                                                 // deleting last tag from tags 

			}

			if (var::removeTag >= 0) {
				var::curTag -= 1;
				if (var::tagcount < 0) {
#ifdef DEB
					std::cout << "No tags to remove..." << std::endl;
#endif
					var::removeTag = -1;
				}
				else {
					sf::Vector2i tagPosition = var::startpoint;
					//tagPosition = var::tags[var::removeTag].getPosition();
					var::tags = tagsNumberChanged(var::removeTag, false);

					for (int i = var::removeTag; i < var::tagcount; ++i) {
						if (i == 0) {
							tagPosition = var::startpoint;
							var::tags[i].setPosition(tagPosition);
						}
						else if (i % 5 == 0) {
							tagPosition.x = var::startpoint.x;
							tagPosition.y += var::indent.y;
							var::tags[i].setPosition(tagPosition);
						}
						else {
							tagPosition.x = var::tags[i - 1].getPosition().x + var::tags[i - 1].getSize().x + var::indent.x;
							var::tags[i].setPosition(tagPosition);
						}
					}
					var::tagPos = tagPosition;
					var::removeTag = -1;

				}
			}

			if (var::addReplace == 1) {

			}

			if (var::applyTo == 1) {

			}

			if (var::setPath == 1) {                                                              // folder selection

				var::shortview = true;
				folder_path.setSelected(true);
				switch (event.type) {
				case sf::Event::TextEntered:
					var::setPath = folder_path.typedOn(event);                                 // function that writes name of the tag

				}
				if (var::setPath == 0) {
					std::string path = folder_path.getText();
					if (formatCheck(path) == ".PNG" || formatCheck(path) == ".JPG" || formatCheck(path) == ".JPEG") {
						imageLoad(path, sf::Vector2i(940, 520));
						var::imgname = path;
						var::resolution = std::to_string(var::texture.getSize().x) + "X" + std::to_string(var::texture.getSize().y);
						ImgInfo.setText(var::imgname, var::resolution, window);
						ImgInfo.show(window);
						var::selected = -1;
					}
					else {
						try {
							open(path);

							menu.update(getcounter(), sf::Vector2i(300, 600), sf::Vector2i(1700, 540));
							for (int i = 0; i < getcounter(); i++) {
								menu.setText(i, getcount(i));
							}
							//std::cout << "file opened" << std::endl;
							var::selected = -1;
						}
						catch (std::exception& ex) {
							std::cout << "Exception in ImageX.cpp: " << ex.what() << std::endl;
						}
					}
					var::shortview = false;
				}
				folder_path.show(window);

			}

			if (var::selected >= 0) {

				if (formatCheck(getcount(var::selected)) == ".PNG" || formatCheck(getcount(var::selected)) == ".JPG" || formatCheck(getcount(var::selected)) == ".JPEG") {
					imageLoad(getFilePath(var::selected), sf::Vector2i(940, 520));
					var::imgname = getcount(var::selected);
					var::resolution = std::to_string(var::texture.getSize().x) + "X" + std::to_string(var::texture.getSize().y);
					ImgInfo.setText(var::imgname, var::resolution, window);
					ImgInfo.show(window);
					var::selected = -1;
				}
				else {
					try {
						open(var::selected);

						menu.update(getcounter(), sf::Vector2i(300, 600), sf::Vector2i(1700, 540));
						for (int i = 0; i < getcounter(); i++) {
							menu.setText(i, getcount(i));
						}
						//std::cout << "file opened" << std::endl;
						var::selected = -1;
					}
					catch (std::exception& ex) {
						std::cout << "Exception in ImageX.cpp: " << ex.what() << std::endl;
					}
				}


			}

			if (var::search_select >= 0) {

				// int ID = getTagID(search_results[var::search_select]);
				// unsigned int* tagged_images = getTaggedImages(ID);
				// searchbar.setText(tagged_images[0]);
				search_menu.setSelected(false);

				var::search_results = 0;

				/* delete */ var::search_results = 1 + search_bar.getText().size();

				search_menu.update(var::search_results /*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 310));
				for (int i = 0; i < var::search_results /*getcounter()*/; i++) {

					search_menu.setText(i, std::to_string(i) /*search_results[i]*/);
				}

				search_bar.setText(std::to_string(var::search_select), window);

				var::search_select = -1;
			}

			if (var::search == 1) {

				var::shortview = true;
				search_bar.setSelected(true);
				search_menu.setSelected(true);
				switch (event.type) {
				case sf::Event::TextEntered:
					var::search = search_bar.typedOn(event);                                 // function that writes name of the tag
					// getSearchResults(&search_results[], image or tag);

				}
				/*searchbar.show(window);*/
				if (var::search == 0) {
					var::shortview = false;

				}
				var::search_results = 0;

				/* delete */ var::search_results = 1 + search_bar.getText().size();

				search_menu.update(var::search_results /*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 310));
				for (int i = 0; i < var::search_results /*getcounter()*/; i++) {

					search_menu.setText(i, std::to_string(i) /*search_results[i]*/);
					search_menu.show(window);
				}

				search_bar.show(window);
				//search_menu.show(window);
			}

			if (var::assign_select >= 0) {
				// int ID = getTagID(assign_results[var::assign_select]);
				// unsigned int* tagged_images = getTaggedImages(ID);
				// assign_bar.setText(tagged_images[0]);
				assign_menu.setSelected(false);

				var::assign_results = 0;

				/* delete */ var::assign_results = 1 + assign_bar.getText().size();

				assign_menu.update(var::assign_results /*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 710));
				for (int i = 0; i < var::assign_results /*getcounter()*/; i++) {

					assign_menu.setText(i, std::to_string(i) /*assign_results[i]*/);
				}

				assign_bar.setText(std::to_string(var::assign_select), window);

				var::assign_select = -1;
			}

			if (var::assign == 1) {

				var::shortview = true;
				assign_bar.setSelected(true);
				assign_menu.setSelected(true);
				switch (event.type) {
				case sf::Event::TextEntered:
					var::assign = assign_bar.typedOn(event);                                 // function that writes name of the tag
					// getAssignResults(&assign_results[], image or tag);

				}
				/*assign_bar.show(window);*/
				if (var::assign == 0) {
					var::shortview = false;

				}
				var::assign_results = 0;

				/* delete */ var::assign_results = 1 + assign_bar.getText().size();

				assign_menu.update(var::assign_results /*getcounter()*/, sf::Vector2i(410, 200), sf::Vector2i(240, 710));
				for (int i = 0; i < var::assign_results /*getcounter()*/; i++) {

					assign_menu.setText(i, std::to_string(i) /*assign_results[i]*/);
					assign_menu.show(window);
				}

				assign_bar.show(window);
			}

			if (var::watchMode == 1) {                                                              // hiding all stuff and projecting the image in fullscreen mode
				var::fullscreen = true;
				float resize = sprite_resize(sf::Vector2i(window.getSize().x, window.getSize().y));

				var::sprite.setScale(sf::Vector2f(1.f / resize, 1.f / resize));
				var::sprite.setPosition(sf::Vector2f(960.f - var::texture.getSize().x / (2 * resize), 520.f - var::texture.getSize().y / (2 * resize)));
			}
			else {
				var::fullscreen = false;
				float resize = sprite_resize(sf::Vector2i(940, 520));

				var::sprite.setScale(sf::Vector2f(1.f / resize, 1.f / resize));
				var::sprite.setPosition(sf::Vector2f(960.f - var::texture.getSize().x / (2 * resize), 490.f - var::texture.getSize().y / (2 * resize)));
			}


			// ======================== Mouse events ===========================

			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				var::exit = Exit.pressed1(var::exit, window);
				if (!var::fullscreen) {
					if (var::shortview != true) {

						// buttons
						var::watchMode = Mod.pressed(var::watchMode, event, window, true);
						var::addTag = Add.pressed(var::addTag, event, window, false);

						var::delTag = Del.pressed(var::delTag, event, window, false);

						var::addReplace = add_replace.pressed(var::addReplace, event, window, false);
						var::applyTo = apply_to.pressed(var::applyTo, event, window, false);

						// textfields
						var::search = search_bar.pressed3(var::search, window);
						var::assign = assign_bar.pressed3(var::assign, window);
						var::setPath = folder_path.pressed3(var::setPath, window);

						// menues
						var::selected = menu.pressed(sf::Mouse::getPosition(window).y, event, window);
						var::search_select = search_menu.pressed(sf::Mouse::getPosition(window).y, event, window);
						var::assign_select = assign_menu.pressed(sf::Mouse::getPosition(window).y, event, window);

						// Image tags

						for (unsigned int i = 0; i < var::tagcount; i++) {
							if (var::tags[i].pressed3(0, window) == 1) {
								var::removeTag = i;
							}
						}


					}
				}
				else {
					var::watchMode = Mod.pressed(var::watchMode, event, window, true);
				}
				break;
			case sf::Event::MouseMoved:
				if (!var::fullscreen) {
					menu.pressed(sf::Mouse::getPosition(window).y, event, window);
					search_menu.pressed(sf::Mouse::getPosition(window).y, event, window);
					assign_menu.pressed(sf::Mouse::getPosition(window).y, event, window);
				}
				break;

			case sf::Event::MouseButtonReleased:

				//if (var::shortview != true) {
				// buttons
				if (!var::fullscreen) {
					var::watchMode = Mod.pressed(var::watchMode, event, window, true);
					Add.pressed(var::addTag, event, window, false);
					var::delTag = Del.pressed(var::delTag, event, window, false);
					var::addReplace = add_replace.pressed(var::addReplace, event, window, false);
					var::applyTo = apply_to.pressed(var::applyTo, event, window, false);

					// textfields
					var::search = search_bar.pressed3(var::search, window);
					var::assign = assign_bar.pressed3(var::assign, window);
					var::setPath = folder_path.pressed3(var::setPath, window);

					//menues
					menu.pressed(sf::Mouse::getPosition(window).y, event, window);
					search_menu.pressed(sf::Mouse::getPosition(window).y, event, window);
					assign_menu.pressed(sf::Mouse::getPosition(window).y, event, window);
					/*menuStatus1 = 0;
					searchStatus = 0;*/
					//}
				}
				else {
					var::watchMode = Mod.pressed(var::watchMode, event, window, true);
				}
				break;
			}

			// -------------------------- drawing all elements ----------------------

			if (!var::fullscreen) {

				ImageField.show(window);
				FolderField.show(window);
				ListField.show(window);
				ImgInfo.show(window);
				Tagicon.show(window);

				folder_path.show(window);
				Add.show(window);
				Del.show(window);
				add_replace.show(window);
				apply_to.show(window);
				search_bar.show(window);
				assign_bar.show(window);

				for (unsigned int i = 0; i < var::tagcount; i++) {
					var::tags[i].show(window, false);
				}


				menu.show(window);
				search_menu.show(window);
				assign_menu.show(window);
			}

			window.draw(var::sprite);
			Exit.show(window);
			Mod.show(window);
			window.display();
		}
	}

	return 0;
}


