#include "font.h"
#include <iostream>

namespace txt {
	//sf::Font font;
	std::string fontname;
}

//sf::Font loadFont(sf::Font font) {
//	if (txt::fontname != "bankgothic-regulardb.ttf") {
//		txt::fontname = "bankgothic-regulardb.ttf";
//
//	}
//	if (!font.loadFromFile("C:/Users/slava/source/repos/ImageX/ImageX/fonts/" + txt::fontname)) {
//		printf("Warning! Unable to load the font!");
//		// return NULL;
//	}
//	else {
//		font.loadFromFile("C:/Users/slava/source/repos/ImageX/ImageX/fonts/" + txt::fontname);
//		return font;
//	}
//}
sf::Font loadFont(sf::Font font) {
	font.loadFromFile("C:/Users/slava/source/repos/ImageX/ImageX/SFramework1.0/fonts/DejaVuSans.ttf");
	//printf("-----");
	return font;
}