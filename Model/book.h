//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_BOOK_H
#define FINAL_PROJECT_BOOK_H
#include <string>

#include "category.h"

using namespace std;

class Book
{
public:
    Book();
    Book(string name, string author, int stock, Category c);

    int getId();

    void setName(string name);
    string getName();

    void setAuthor(string author);
    string getAuthor();

    void setStock(int stock);
    int getStock();

    void setRating(float rating);
    float getRating() const;

    void setCategory(Category c);
    Category getCategory();

private:
    static int counter;
    int id;
    string name;
    string author;
    int stock;
    float rating;
    Category category;
};
#endif //FINAL_PROJECT_BOOK_H
