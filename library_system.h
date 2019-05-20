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

class LibrarySystem{
private:
    vector<User> listUser;
    vector<Book> listBook;
    vector<Category> listCategory;
    vector<Transaction> listTransaction;

public:
    // -- User operations --
    LibrarySystem();
    void addUser(User u);
    void removeUser(int position);
    void updateUser(int position,User u);

    vector<User> getListUser();

    // -- Login --
    bool doLogin(string username, string password, User& u);
    // -- Book operations --

    void addBook(Book b);
    void removeBook(int position);
    void updateBook(int position,Book b);
    bool searchBook();
    int searchBook(int id);
    void displayBooks();
    void displayBorrowedBooks();
    void displayTopBorrowedMonthlyBooks(string date);
    void displayTopRatedMonthlyBooks(string date);

    // -- Category operations --
    int addCategory(Category c);
    Category getCategory(int position);
    void removeCategory(int position);
    void updateCategory(int position, Category c);
    bool searchCategory();
    int searchCategory(int id);
    void displayCategories();

    // -- Transaction operations --
    void addTransaction(Transaction t);
    void updateTransactionStatus(int position, string s);
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
