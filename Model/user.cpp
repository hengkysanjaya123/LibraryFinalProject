//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "user.h"

User::User(){

}

User::User(string n, string u, string p, string r){
    this->name = n;
    this->username = u;
    this->password = p;
    this->role = r;
    this->level = 1;
    this->booklim = 2;
    this->reqExp = 3;
}

void User::setName(string name) {
    this->name = name;
}

string User::getName() {
    return this->name;
}

void User::setUsername(string username) {
    this->username = username;
}

string User::getUsername() {
    return this->username;
}

void User::setPassword(string password) {
    this->password = password;
}

string User::getPassword() {
    return this->password;
}

void User::setRole(string role) {
    this->role = role;
}

string User::getRole() {
    return this->role;
}

void User::setLevel(int level){
    this->level = level;
}

int User::getLevel(){
    return this->level;
}

void User::setBooklim(int limit) {
    this->booklim = limit;
}

int User::getBooklim() {
    return this->booklim;
}
void User::addExp() {
    this->exp++;

}

void User::levelCheck() {

    if (this->exp >= this->reqExp && this->level < 5){
        this->level += 1;
        this->booklim++;
        this->exp = 0;

        cout << "You are now level " << this->level << " and your borrow limit has been increased to " << this->booklim << " books." << endl;
    }

}
