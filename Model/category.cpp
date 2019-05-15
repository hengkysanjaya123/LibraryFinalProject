//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "category.h"

Category::Category()
{
}

Category::Category(string name)
{
    this->name = name;
}

void Category::setName(string name)
{
    this->name = name;
}

string Category::getName()
{
    return this->name;
}




