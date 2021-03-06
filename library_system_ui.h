//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_LIBRARY_SYSTEM_UI_H
#define FINAL_PROJECT_LIBRARY_SYSTEM_UI_H

#include <iostream>
#include <ctime>
#include "library_system.h"

using namespace std;

class LibrarySystemUI {
private:
    LibrarySystem ls;
public:
    void run();

    void adminPage(User currentUser);

    void userPage(User currentUser);

    int addCategoryUI();

    string enterPassword();

    vector<string> split(string text, char delimiter);

    vector<vector<string>> readFile(string filename);

    void writeFile(string filename, vector<string> list);
};


#endif //FINAL_PROJECT_LIBRARY_SYSTEM_UI_H
