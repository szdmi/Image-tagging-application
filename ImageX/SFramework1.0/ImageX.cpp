
#include <math.h>
#include "icon.h"
//#include "win.h"
#include "scroll_menu.h"
#include "C:\Users\slava\source\Laboratory\Испытательная\Испытательная\fmgr.h"

//#define MAX_TAGS = 15

//#define DEB      // debug mode



namespace var {
    short int exit = 0;                                                 // buttons variables
    short int addTag = 0;
    short int delTag = 0;
    short int changeMod = 0;
    short int selFolder = 0;
    short int watchMode = 0;

    std::string imgname = "image name.jpg";
    std::string resolution = "1920 x 1080";
    
    bool shortview = false;                                             // no button`s are active ( except of chosen one and the exit button ) while this variable is true
    sf::Vector2i startpoint(550, 880);                                  // first tag position
    tag* tags;                                                          // tags array pointer
    int tagcount = 0;                                                   
    tag tagCount[15];                                                   // static array ( in case if something wrong will happen with the dynamic one )  
    
    int curTag = 0;
    sf::Vector2i curtagpos = startpoint;                                // position of the last tag

    sf::Texture texture;                                                // for image(texture/sprite) loading
    sf::Sprite sprite;
    std::string curFolder;
    short int selected = -1;

    short int selected2 = -1;
}



static tag* tagsNumberChanged(short int n, bool add_or_delete) {

    if (add_or_delete == true) {                                        // true == add         false == delete     
        n = var::tagcount;                                              // n - place in array to insert a new tag ( at the end by default )
        tag* p;
        var::tagcount += 1;
        p = new tag[var::tagcount];                                     // creating new array of tags
        for (int i = 0; i < var::tagcount; i++) {
            if (i > n) {
                p[i] = var::tags[i-1];
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
        return p;
    }
    else {
        tag* p;
        var::tagcount -= 1;
        p = new tag[var::tagcount];                                     //creating new array
        for (int i = 0; i < var::tagcount; i++) {
            if (i > n) {
                p[i-1] = var::tags[i];
            }
            else if (i == n) {
                var::tags[i].deleteTag();
            }
            else {
                p[i] = var::tags[i];
            }
        }
        delete[] var::tags;                                             // deleting the old one
        return p;
    }
    

}

void imageLoad(int n, sf::Vector2i field, sf::RenderWindow& window) {
    //texture.create(400, 400);
    //image.loadFromFile(getFilePath(n));
    var::texture.loadFromFile(getFilePath(n));
    var::sprite.setTexture(var::texture, true);
    //var::sprite.setPosition(sf::Vector2f(960.f - float(field.x/2), 490.f - float(field.y/2)));
    sf::Vector2u texture_size = var::texture.getSize();
    float resize = 0.f;

    //resize = float(texture_size.x) / field.x;
    //resize = float(texture_size.y) / field.y;
    if (float(texture_size.x) / field.x > float(texture_size.y) / field.y) {
        resize = float(texture_size.x) / field.x;
    }
    else {
        resize = float(texture_size.y) / field.y;
    }

    var::sprite.setScale(sf::Vector2f(1.f / resize, 1.f / resize));
    var::sprite.setPosition(sf::Vector2f(960.f - var::texture.getSize().x / (2*resize), 490.f - var::texture.getSize().y / (2* resize)));
    std::cout << var::texture.getSize().x << " size " << std::endl;

};

int main() {
    
    std::string textbuffer;
    sf::RenderWindow window;
    window.create(sf::VideoMode(1920, 1080), "ImageX", sf::Style::Fullscreen);                      // creating main window
    unsigned int menuStatus1 = 0;
    unsigned int menuStatus2 = 0;

    var::tags = new tag[1];                                                                         // array of tags of the image
    var::tagcount = 1;                                                                              // tagcount must be always bigger by 1, because of addTag function 
    
    //====== file manager ======
    launch();
    open(0);
    scroll_menu menu(getcounter(), sf::Vector2i(300, 600), sf::Vector2i(1700, 540), false);         // set count of objects

    scroll_menu menu2(15, sf::Vector2i(350, 300), sf::Vector2i(240, 230), true);
    menu2.setColour(150, 150, 150, 2);
    for (int i = 0; i < getcounter(); i++) {
        menu.setTxt(i, getcount(i));
    }

    for (int i = 0; i < 15; i++) {
        menu2.setTxt(i, std::to_string(i));
    }
    
    

    while (window.isOpen()) {
        sf::Event evnt;
        sf::Vector2i mousepos = sf::Mouse::getPosition(window);                                     // current mouse position 

        while (window.pollEvent(evnt)) {                                                            // main event loop

        window.clear(sf::Color(0, 0, 0));
        sf::Vector2i scale = sf::Vector2i(300, 50);
        sf::Vector2i pos = sf::Vector2i(330, 70);



        // ====== Exit button =======                                                               // initialization sequence
        char exit[12] = "Exit";
        button Exit(sf::Vector2i(100, 40), sf::Vector2i(60, 30), window, exit);
        Exit.show(window);

        //====== change mod button ======
        char mod[12] = "watch";
        button Mod(sf::Vector2i(300, 40), sf::Vector2i(250, 30), window, mod);
        Mod.show(window);

        //====== select folder button ======
        char folder[] = "Select folder";
        button Folder(sf::Vector2i(300, 40), sf::Vector2i(1700, 200), window, folder);
        Folder.show(window);

        //====== Add tag button ======
        char add[] = "Add tag";
        button Add(sf::Vector2i(200, 40), sf::Vector2i(140, 900), window, add);
        Add.show(window);

        //====== Delete tag button ======
        char del[12] = "Del tag";
        button Del(sf::Vector2i(200, 40), sf::Vector2i(340, 900), window, del);
        Del.show(window);

        //====== basic fields ======
        field Field1(sf::Vector2i(480, 900), sf::Vector2i(720, 540), window);
        Field1.show(window);

        field Field2(sf::Vector2i(480, 900), sf::Vector2i(1200, 540), window);
        Field2.show(window);

        field Field3(sf::Vector2i(300, 600), sf::Vector2i(1700, 540), window);
        Field3.show(window);
        //====== list`s field ======
        field ListField(sf::Vector2i(410, 680), sf::Vector2i(240, 520), window);
        ListField.show(window);

        //====== Image Icon ======
        
        icon ImgInfo(sf::Vector2i(960, 100), sf::Vector2i(960, 140), window, var::imgname, var::resolution);
        ImgInfo.show(window);
        //====== tags Icon ======
        std::string tagicon = "Image tags:";
        icon Tagicon(sf::Vector2i(960, 30), sf::Vector2i(960, 840), window, tagicon);
        Tagicon.show(window);
        
        
                                                                                                    // button functions 
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {                                 // close the program
                window.close();
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {                                      // debug stuff
                if (var::shortview == false) {
                    var::addTag = 1;
                }
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {                                      // debug stuff
                if (var::shortview == false) {
                    var::delTag = 1;
                }
            }
            if (var::exit == 1) {                                                                   // close the program
                window.close();
                break;
            }

            if (var::addTag == 1) {                                                                 // adding new tag to tags array
                var::shortview = true;

                if (var::curTag > 14) {                                                             // some checks
                    //window.close();
                    std::cout << "Max number of tags reached!" << var::curTag <<std::endl;
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

                        var::tags[var::curTag].setSel(true);                                                    // set on selection of the tag (planned, but not currently in use )
                        var::tags[var::curTag].tagshow(1);                                                      // allowing the tag to display (only for static array usage)
                        var::tags[var::curTag].setPosition(sf::Vector2i(var::curtagpos.x, var::curtagpos.y));   // setting tag`s position
                        switch (evnt.type) {
                        case sf::Event::TextEntered:
                            var::addTag = var::tags[var::curTag].typedOn(evnt);                                 // function that writes name of the tag
                            //case sf::Event::MouseButtonPressed:

                        }
                        var::tags[var::curTag].show(window);
                    
                    ///////////////////////////////

                    if (var::addTag == 0) {
                        try {
                        var::tags = tagsNumberChanged(var::curTag, true);                                   // expanding tags array at 1
                        std::cout << var::tags[var::curTag].getPosition().x<< "<<<<<<" << std::endl;        // 
                        if ((var::curTag + 1) % 5 == 0) {                                                   // calculating future tag`s position
                            var::curTag += 1;
                            var::curtagpos.x = var::startpoint.x;
                            var::curtagpos.y += 40;
                            var::shortview = false;
                        }
                        else {
                            var::curtagpos.x = var::tags[var::curTag].getPosition().x + int(var::tags[var::curTag].getlength());
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
                    var::curTag -= 1;
                    if (var::curTag < 0) {                                                          // some checks
                        var::curTag = 0;
                        #ifdef DEB
                        std::cout << "No tags to delete..." << std::endl;
                        #endif
                        var::delTag = 2;
                    }
                    else if (var::curTag < -1 || var::curTag > 14) {
                        std::cout << "curTag alert! " << var::curTag << std::endl;
                        window.close();
                    }
                    else {
                        if ((var::curTag + 1) % 5 == 0) {                                           //recalculating future tag`s position
                            var::curtagpos.x = var::tags[var::curTag].getPosition().x;
                            var::curtagpos.y -= 40;
                            var::tags = tagsNumberChanged(var::curTag, false);                      //squizzing tags array at 1 and deleting the last tag
                            var::delTag = 2;
                            #ifdef DEB
                            std::cout << "deltag sequence done" << std::endl;
                            #endif
                        }
                        else {
                            var::curtagpos.x = var::tags[var::curTag].getPosition().x;
                            var::tags = tagsNumberChanged(var::curTag, false);
                            var::delTag = 2;
                            #ifdef DEB
                            std::cout << "deltag sequence done" << std::endl;
                            #endif
                        }
                    }
            }
            #ifdef DEB
            std::cout << var::tags[0].getPosition().x <<"real tag position" << std::endl;
            #endif

            for (unsigned int i = 0; i < var::tagcount; i++) {
                var::tags[i].show(window);                                                          // display all active tags on the screen
            }

            if (var::changeMod == 1) {                                                              // changing 'edit' and 'watch' modes 
                //-------
            }
            if (var::selFolder == 1) {                                                              // folder selection
                //win window2;                                                                      // additional window generation
                //var::shortview = true;                                                            // disable main window buttons
                //var::selFolder = window2.winprocess();                                            // activate the additional window
                //std::cout << var::selFolder << std::endl;
                //var::selFolder = 0;
                //var::shortview = false;                                                           // enable buttons
                

            }
            if (var::selected >= 0) {
                if (formatCheck(getcount(var::selected)) == ".PNG" || formatCheck(getcount(var::selected)) == ".JPG" || formatCheck(getcount(var::selected)) == ".JPEG") {
                    imageLoad(var::selected, sf::Vector2i(940, 520), window);
                    var::imgname = getcount(var::selected);
                    var::resolution = std::to_string(var::texture.getSize().x) + "X" + std::to_string(var::texture.getSize().y);
                    ImgInfo.show(window);
                    var::selected = -1;
                }
                else {
                    open(var::selected);

                    menu.update(getcounter(), sf::Vector2i(300, 600), sf::Vector2i(1700, 540));
                    for (int i = 0; i < getcounter(); i++) {
                        menu.setTxt(i, getcount(i));
                    }
                    std::cout << "file opened" << std::endl;
                    var::selected = -1;
                }

            }

            if (var::selected2 >= 0) {
                //var::addTag = 1;
                menu2.update(15, sf::Vector2i(350, 300), sf::Vector2i(240, 230));
                for (int i = 0; i < 15; i++) {
                    menu2.setTxt(i, std::to_string(i));
                }
                var::selected2 = -1;
            }

            if (var::watchMode == 1) {                                                              // hiding all stuff and projecting the image in fullscreen
                //-------
            }
            //======
            
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {                                      // mouse pressed function calls

                var::exit = Exit.pressed1(var::exit);
                if (var::shortview != true) {
                    var::watchMode = Mod.pressed2(var::watchMode, evnt);
                    var::selFolder = Folder.pressed2(var::selFolder, evnt);
                    var::addTag = Add.pressed2(var::addTag, evnt);
                    var::delTag = Del.pressed2(var::delTag, evnt);
                    if (menu.pressed(sf::Mouse::getPosition(window).y, evnt, window) >= 0) {
                        var::selected = menu.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    }
                    else {
                        menu.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    }
                    if (menu2.pressed(sf::Mouse::getPosition(window).y, evnt, window) >= 0) {
                        var::selected2 = menu2.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    }
                    else {
                        menu2.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    }
                    menu.show(window);
                    menu2.show(window);
                    menuStatus1 = 1;
                    menuStatus2 = 1;
                    //status = Field1.pressed(window);                                              // это поля перещелкивания между изображенями в папке
                    //status = Field2.pressed(window);
                    
                }

                                                                                                    // display all the buttons
                Exit.show(window);
                Mod.show(window);
                Folder.show(window);
                Add.show(window);
                Del.show(window);
                
                //Field1.show(window);                                                              // отображение полей перещелкивания 
                //Field2.show(window);

            }
            else if (evnt.type == sf::Event::MouseMoved) {
                if (menuStatus1 == 1) {
                    menu.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    menu.show(window);
                }
                else if (menuStatus2 == 1) {
                    menu2.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    menu2.show(window);
                }
                #ifdef DEB
                std::cout << "button moved" << std::endl;
                #endif
            }
            else if (evnt.type == sf::Event::MouseButtonReleased) {                                      // mouse released function calls
                if (var::shortview != true) {
                    var::watchMode = Mod.pressed2(var::watchMode, evnt);
                    var::selFolder = Folder.pressed2(var::selFolder, evnt);
                    var::addTag = Add.pressed2(var::addTag, evnt);
                    var::delTag = Del.pressed2(var::delTag, evnt);
                    menu.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    menu2.pressed(sf::Mouse::getPosition(window).y, evnt, window);
                    menu.show(window);
                    menu2.show(window);
                    menuStatus1 = 0;
                    menuStatus2 = 0;
                }
            }
            window.draw(var::sprite);
            menu.show(window);
            menu2.show(window);
            window.display();
        }
    }
        
        return 0;
    }


