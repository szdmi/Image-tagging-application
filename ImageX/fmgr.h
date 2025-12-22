#pragma once
#include <iostream>
#include <fstream>
#include <dirent.h>

    

    

    void launch();                              // sets the initial folder (Images by default)

    int getcounter();

    void setfilter(std::string extention);   // shows only images with specified file extentions
    
    bool removefilter(std::string extention);

    std::string getcount(int n);                // return the name of file/folder with index n

    void open(std::string nextf);               // open the image/directory by entering a full path

    void open(int n);                           // open the image/directory from a current folder

    std::string formatCheck(std::string n);             // checks if that is an image or folder

    //void selectf();                              // reads txt files

    void close();

    std::string getFilePath(int n);

