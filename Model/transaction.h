//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_TRANSACTION_H
#define FINAL_PROJECT_TRANSACTION_H


#include <string>
#include "user.h"
#include "book.h"

using namespace std;
class Transaction
{
public:
    Transaction();
    Transaction(User user, Book book, string status, string date, string review);

    void setUser(User user);
    User getUser();

    void setBook(Book book);
    Book getBook();

    void setStatus(string status);
    string getStatus();

    void setDate(string date);
    string getDate();

    void setReview(string review);
    string getReview();

private:
    User user;
    Book book;
    string status;
    string date;
    string review;


};

#endif //FINAL_PROJECT_TRANSACTION_H
