//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "book.h"

Book::Book()
{

}

int Book::counter;

// book constructor
Book::Book(string name, string author, int stock, Category c)
{
    counter++;
    this->id = counter;
    this->name = name;
    this->author = author;
    this->stock = stock;
    this->rating = 0;
    this->category = c;
}

// function to set book's name
void Book::setName(string name)
{
    this->name = name;
}

// function to get book's name
string Book::getName()
{
    return this->name;
}

// function to set book's author
void Book::setAuthor(string author)
{
    this->author = author;
}

// function to get book's author
string Book::getAuthor()
{
    return this->author;
}

// function to set book's stock
void Book::setStock(int stock)
{
    this->stock = stock;
}
// function to get stock
int Book::getStock()
{
    return this->stock;
}

// function to set rating
void Book::setRating(float rating)
{
    this->rating = rating;
}

// function to get rating
float Book::getRating() const
{
    return this->rating;
}

// function to get book's id
int Book::getId() {
    return this->id;
}

// function to set category
void Book::setCategory(Category c){
    this->category = c;
}

// function to get category
Category Book::getCategory(){
    return this->category;
}
