//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_CATEGORY_H
#define FINAL_PROJECT_CATEGORY_H

#include <string>
using namespace std;
class Category
{
public:
    Category();
    Category(string name);

    void setName(string name);
    string getName();

private:
    string name;
};

#endif //FINAL_PROJECT_CATEGORY_H
