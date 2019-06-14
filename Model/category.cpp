//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "category.h"

Category::Category() {
}

int Category::counter;

Category::Category(string name) {
    counter++;
    this->name = name;
    this->id = counter;
}

void Category::setName(string name) {
    this->name = name;
}

string Category::getName() {
    return this->name;
}

int Category::getId() {
    return this->id;
}

int Category::getStock() {

};

string Category::getAuthor() {

};



