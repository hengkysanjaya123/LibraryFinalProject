//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "user.h"

User::User(){

}

User::User(string n, string u, string p, string r, int level, int booklim, int reqExp, int exp){
    this->name = n;
    this->username = u;
    this->password = p;
    this->role = r;
    this->level = level;
    this->booklim = booklim;
    this->reqExp = reqExp;
    this->exp = exp;
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

int User::getExp() {
    return this->exp;
}

void User::setExp(int exp) {
    this->exp = exp;
}

int User::getReqExp() {
    return this->reqExp;
}

void User::setreqExp(int reqExp) {
    this->reqExp = reqExp;
}

int User::getBooklim() {
    return this->booklim;
}
void User::addExp() {
    this->exp += 1;

}

void User::levelCheck() {

    if (this->exp >= this->reqExp && this->level < 5){
        this->level += 1;
        this->booklim++;
        this->exp = 0;

        cout << "You are now level " << this->level << " and your borrow limit has been increased to " << this->booklim << " books." << endl;
    }

}
