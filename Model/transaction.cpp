//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "transaction.h"

Transaction::Transaction() {
}

Transaction::Transaction(User user, Book book, string status, string date, string duedate, string review, int rating) {
    this->user = user;
    this->book = book;
    this->status = status;
    this->date = date;
    this->duedate = duedate;
    this->review = review;
    this->rating = rating;
}

void Transaction::setUser(User user) {
    this->user = user;
}

User Transaction::getUser() {
    return this->user;
}

void Transaction::setBook(Book book) {
    this->book = book;
}

Book Transaction::getBook() {
    return this->book;
}

void Transaction::setStatus(string status) {
    this->status = status;
}

string Transaction::getStatus() {
    return this->status;
}

void Transaction::setDate(string date) {
    this->date = date;
}

string Transaction::getDate() {
    return this->date;
}

void Transaction::setDuedate(string duedate) {
    this->duedate = duedate;
}

string Transaction::getDuedate() {
    return this->duedate;
}

void Transaction::setReview(string review) {
    this->review = review;
}

string Transaction::getReview() {
    return this->review;
}


void Transaction::setRating(int rating) {
    this->rating = rating;
}

int Transaction::getRating() {
    return this->rating;
}