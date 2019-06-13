//
// Created by Hengky Sanjaya on 5/15/2019.
//

#ifndef FINAL_PROJECT_LIBRARY_SYSTEM_H
#define FINAL_PROJECT_LIBRARY_SYSTEM_H


#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

#include "Model/book.h"
#include "Model/user.h"
#include "Model/category.h"
#include "Model/transaction.h"

using namespace std;

class LibrarySystem {
private:
    User currentUser;
    vector<User> listUser;
    vector<Book> listBook;
    vector<Category> listCategory;
    vector<Transaction> listTransaction;


public:
    void WriteWithColor(string message, char color);

    void SetTextColor(char color);

    void ResetTextColor();

    string toLower(string text);

    bool IsUsernameExist(string username);

    User getCurrentUser();

    void setCurrentUser(User u);

    // -- User operations --
    LibrarySystem();

    void addUser(User u);

    void removeUser(int position);

    void updateUser(int position, User u);

    vector<User> getListUser();

    vector<string> getUsersinFormat();

    // -- Login --
    bool doLogin(string username, string password, User &u);
    // -- Book operations --

    void addBook(Book b);

    void removeBook(int position);

    void updateBook(int position, Book b);

    bool searchBook();

    int searchBook(int id);

    void displayBooks();

    void displayBorrowedBooks();

    void displayBorrowedBooks(User u);

    void displayTopBorrowedBooks(string date, int option);

    void displayTopRatedBooks(string date, int option);

    vector<string> getBooksInFormat();


    // -- Category operations --
    int addCategory(Category c);

    Category getCategory(int position);

    void removeCategory(int position);

    void updateCategory(int position, Category c);

    vector<string> getCategoriesInFormat();

    bool searchCategory();

    int searchCategory(int id);

    void displayCategories();

    vector<Category> getListCategory();

    // -- Transaction operations --
    void addTransaction(int bookPosition);

    bool returnBook(int bookId);

    void updateTransactionStatus(int bookposition);

    void viewTodaysTransactions(string date);

    void viewMonthlyTransactions(string date);

    void viewAllTransactions();

    void testing(int a);





    //		list<User>* getListUser(){
    //			return &(this->listUser);
    //		}

    //		template<class T>
    //		void add(T obj, list<T>& list){
    //			list.push_back(obj);
    //		}

    //		template<class T>
    //		void remove(T obj, list<T>& list){
    //			for(int i = 0;i < list.size();i++){
    //				if(list[i] == obj){
    //					list.remove(list[i]);
    //					break;
    //				}
    //			}
    //		}

    //		template<class T>
    //		void update(T beforeObj, list<T> list, T afterObj){
    //			for(int i = 0;i < list.size();i++){
    //				if(list[i] == beforeObj){
    //					list[i] = afterObj;
    //					break;
    //				}
    //			}
    //		}
};


#endif //FINAL_PROJECT_LIBRARY_SYSTEM_H
