//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_USER_H
#define FINAL_PROJECT_USER_H


#include <iostream>
using namespace std;

class User
{
private:
    string name;
    string username;
    string password;
    string role;

    int level;
    int booklim;
    int reqExp;
    int exp;


public:
    User();
    User(string n, string u, string p, string r, int level, int booklim, int reqExp, int exp);

    void setName(string name);
    string getName();

    void setUsername(string username);
    string getUsername();

    void setPassword(string password);
    string getPassword();

    void setRole(string role);
    string getRole();

    void setLevel(int level);
    int getLevel();

    void setBooklim(int limit);
    int getBooklim();

    void setExp(int exp);
    int getExp();

    void setreqExp(int reqExp);
    int getReqExp();

    void addExp();
    void levelCheck();


};

#endif //FINAL_PROJECT_USER_H
