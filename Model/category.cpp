//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "category.h"

Category::Category() {
}

int Category::counter;

// category constructor
Category::Category(string name) {
    counter++;
    this->name = name;
    this->id = counter;
}

// function to set name
void Category::setName(string name) {
    this->name = name;
}

// function to get name
string Category::getName() {
    return this->name;
}

// function to get id
int Category::getId() {
    return this->id;
}

int Category::getStock() {

};


string Category::getAuthor() {

};



