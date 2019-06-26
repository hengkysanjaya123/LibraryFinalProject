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
    Transaction(User user, Book book, string status, string date, string duedate, string review, int rating);

    void setUser(User user);
    User getUser();

    void setBook(Book book);
    Book getBook();

    void setStatus(string status);
    string getStatus();

    void setDate(string date);
    string getDate();

    void setDuedate(string duedate);
    string getDuedate();

    void setReview(string review);
    string getReview();

    void setRating(int rating);
    int getRating();

private:
    User user;
    Book book;
    string status;
    string date;
    string duedate;
    string review;
    int rating;


};

#endif //FINAL_PROJECT_TRANSACTION_H
