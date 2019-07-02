//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "user.h"

User::User(){

}

// user constructor
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

// function to set name
void User::setName(string name) {
    this->name = name;
}

// function to get name
string User::getName() {
    return this->name;
}

// function to set username
void User::setUsername(string username) {
    this->username = username;
}

// function to get username
string User::getUsername() {
    return this->username;
}

// function to set password
void User::setPassword(string password) {
    this->password = password;
}

// function to get password
string User::getPassword() {
    return this->password;
}

// function to set role
void User::setRole(string role) {
    this->role = role;
}

// function to get role
string User::getRole() {
    return this->role;
}

// function to set level
void User::setLevel(int level){
    this->level = level;
}

// function to get level
int User::getLevel(){
    return this->level;
}

// function to set book limit
void User::setBooklim(int limit) {
    this->booklim = limit;
}

// function to get exp
int User::getExp() {
    return this->exp;
}

// function to set exp
void User::setExp(int exp) {
    this->exp = exp;
}

// function to get required exp
int User::getReqExp() {
    return this->reqExp;
}

// function to set required exp
void User::setreqExp(int reqExp) {
    this->reqExp = reqExp;
}

// function to get book limit
int User::getBooklim() {
    return this->booklim;
}
// function to add exp
void User::addExp() {
    this->exp += 1;

}
// function to check level
void User::levelCheck() {

    if (this->exp >= this->reqExp && this->level < 5){
        this->level += 1;
        this->booklim++;
        this->exp = 0;

        cout << "You are now level " << this->level << " and your borrow limit has been increased to " << this->booklim << " books." << endl;
    }

}
