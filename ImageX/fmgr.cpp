#include "fmgr.h"
#include <list>
//#define MBL 100 // standart 'count' length (100 items in one 'count')

DIR* pd = 0;
std::fstream fs;
std::string buffer;
std::string dirname;
struct dirent* dent;
std::list<std::string> count;
std::list<std::string>::iterator counter;
std::list<std::string> filters;
std::list<std::string>::iterator fil_counter;


void launch() {
    
    dirname = "C:/Users/slava";
    if (dirname == "") {
        std::cout << "not found ";
        exit(1);
    }
    
}

int getcounter() {
    return count.size();
};

void setfilter(std::string extention) {
    filters.push_back(formatCheck(extention));
}

bool removefilter(std::string extention) {
    fil_counter = filters.begin();
    int i = 0;
    while (i < filters.size()) {
        if (*fil_counter == formatCheck(extention)) {
            filters.erase(fil_counter);
            return false;
        }
        ++fil_counter;
        ++i;
    }
    return true;
}

std::string getcount(int n) {
    counter = count.begin();
    std::advance(counter, n);
    return *counter;
}

std::string formatCheck(std::string st) {


    std::string newst;
    //st = getcount(n);
    int j = st.length();
    while (j >= 0) {
        newst = st[j];
        if (newst == ".") {
            newst = "";
            while (j < st.length()) {
                newst += toupper(st[j]);
                j++;
            }
            return newst;
            break;
        }
        else {
            j -= 1;
        }
    }
    return "";




}


void open(std::string fullpath) {     //  if you enter image/directory full path
    try {
    if (fullpath != "") {
        count.clear();
        pd = opendir((fullpath).c_str());
        dirname = fullpath;
    }
    else {
        count.clear();
        pd = opendir((dirname).c_str());
    }
    do {
        dent = readdir(pd);
        if (dent)
        {
            buffer = dent->d_name;
            if (dent->d_type == DT_DIR) {
                count.push_back(dent->d_name);
            }
            else {
                if (filters.size() > 0) {
                    fil_counter = filters.begin();
                    for (int i = 0; i < filters.size(); ++i, ++fil_counter) {
                        if (*fil_counter == formatCheck(buffer)) {
                            count.push_back(buffer);
                            break;
                        }
                    }
                }
                else {
                    count.push_back(buffer);
                }
            }

            //}
        }
    } while (dent);
    closedir(pd);
    }
    catch (std::exception& excpetion) {

        std::cout << "ERROR" << std::endl;
    }
}

void open(int n) {                              // navigating through a folder with array indexes
    try {
        if (n != 0) {

            pd = opendir((dirname + "/" + getcount(n)).c_str());
            dirname = dirname + "/" + getcount(n);
            count.clear();



            std::cout << dirname << std::endl;
        }
        /*else if (n == 1) {
            std::string nt;
            int i = dirname.length();
            while (nt != "/") {
                nt += dirname[i];
                i -= 1;
            }
            reverse(nt.begin(), nt.end());

        }*/
        else {
            count.clear();
            pd = opendir((dirname).c_str());
        }
        //counter = count.begin();
        do {
            dent = readdir(pd);
            if (dent)
            {
                buffer = dent->d_name;
                if (dent->d_type == DT_DIR) {
                    count.push_back(dent->d_name);
                }
                else {
                    if (filters.size() > 0) {
                        fil_counter = filters.begin();
                        for (int i = 0; i < filters.size(); ++i, ++fil_counter) {
                            if (*fil_counter == formatCheck(buffer)) {
                                count.push_back(buffer);
                                break;
                            }
                        }
                    }
                    else {
                        count.push_back(buffer);
                    }
                }
            }
        } while (dent);
        closedir(pd);
    }
    catch (std::exception& excpetion) {

        std::cout << "ERROR" << std::endl;
    }
}





void selectf() {
    std::cout << "Select file:" << std::endl;
    std::cin >> buffer;
    if (buffer != "-1") {
        fs.open(dirname + buffer, std::fstream::in);
        while (!fs.eof()) {
            buffer = "";
            fs >> buffer;
            std::cout << buffer << std::endl;
        }
        fs.close();
    }
}

void close() {
    
    count.clear();
}

std::string getFilePath(int n) {
    return dirname + "/" + getcount(n);
};