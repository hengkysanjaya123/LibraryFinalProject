//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "user.h"

User::User(){

}

User::User(string n, string u, string p, string r){
    name = n;
    username = u;
    password = p;
    role = r;
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

void User::setLevel(string level){
    this->level = level;
}

string User::getLevel(){
    return this->level;
}
