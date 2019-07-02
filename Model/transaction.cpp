//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "transaction.h"

Transaction::Transaction() {
}

// transaction constructor
Transaction::Transaction(User user, Book book, string status, string date, string duedate, string review, int rating) {
    this->user = user;
    this->book = book;
    this->status = status;
    this->date = date;
    this->duedate = duedate;
    this->review = review;
    this->rating = rating;
}
// function to set user
void Transaction::setUser(User user) {
    this->user = user;
}

// function to get user
User Transaction::getUser() {
    return this->user;
}

// function to set book
void Transaction::setBook(Book book) {
    this->book = book;
}

// function to get book
Book Transaction::getBook() {
    return this->book;
}

// function to set status
void Transaction::setStatus(string status) {
    this->status = status;
}

// function to get status
string Transaction::getStatus() {
    return this->status;
}

// function to set date
void Transaction::setDate(string date) {
    this->date = date;
}

// function to get date
string Transaction::getDate() {
    return this->date;
}

// function to set due date
void Transaction::setDuedate(string duedate) {
    this->duedate = duedate;
}

// function to get due date
string Transaction::getDuedate() {
    return this->duedate;
}

// function to set review
void Transaction::setReview(string review) {
    this->review = review;
}

// function to get review
string Transaction::getReview() {
    return this->review;
}

// function to set rating
void Transaction::setRating(int rating) {
    this->rating = rating;
}

// function to get rating
int Transaction::getRating() {
    return this->rating;
}