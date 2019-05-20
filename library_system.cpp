//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system.h"

LibrarySystem::LibrarySystem() {
}

// -- User operations --
void LibrarySystem::addUser(User u) {
    listUser.push_back(u);
}

void LibrarySystem::removeUser(int position) {
    listUser.erase(listUser.begin() + position);
}

void LibrarySystem::updateUser(int position, User u) {
    listUser[position].setName(u.getName());
    listUser[position].setUsername(u.getUsername());
    listUser[position].setPassword(u.getPassword());
    listUser[position].setRole(u.getRole());
    listUser[position].setLevel(u.getLevel());
    cout << "x";
}

vector<User> LibrarySystem::getListUser() {
    return listUser;
}

// -- Login --
bool LibrarySystem::doLogin(string username, string password, User &u) {
    for (int i = 0; i < listUser.size(); i++) {
        User cur = listUser[i];
        if (cur.getUsername() == username && cur.getPassword() == password) {
            u = cur;
            return true;
        }
    }
    return false;
}

// -- Book operations --

void LibrarySystem::addBook(Book b) {
    listBook.push_back(b);
}

void LibrarySystem::removeBook(int position) {
    listBook.erase(listBook.begin() + position);
}

void LibrarySystem::updateBook(int position, Book b) {
    listBook[position].setName(b.getName());
    listBook[position].setAuthor(b.getAuthor());
    listBook[position].setStock(b.getStock());
}

int LibrarySystem::searchBook(int id) {
    for (int i = 0; i < listBook.size(); ++i) {
        if (listBook[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

bool LibrarySystem::searchBook() {
    int suboption_book_search;
    string key;
    cout << "Search book by : " << endl
         << "1. Name" << endl
         << "2. Author" << endl
         << ">>";
    cin >> suboption_book_search;

    if (suboption_book_search == 1) {
        cout << "Input book name >>";
        cin >> key;
    } else if (suboption_book_search == 2) {
        cout << "Input Author name >>";
        cin >> key;
    }

    bool found = false;
    vector<int> listFound;

    for (int i = 0; i < listBook.size(); ++i) {
        if (suboption_book_search == 1) {
            if (listBook[i].getName() == key) {
                found = true;
                listFound.push_back(i);
            }
        } else if (suboption_book_search == 2) {
            if (listBook[i].getAuthor() == key) {
                found = true;
                listFound.push_back(i);
            }
        }
    }

    if (found) {
        printf("%-20s | %-20s | %-20s | %-20s | %-20s | %-20s |\n", "ID", "Name", "Author", "Stock", "Rating", "Category");
        for (int j = 0; j < listFound.size(); ++j) {
            int i = listFound[j];
            printf("%-20d | %-20s | %-20s | %-20d | %-20d | %-20s |\n", listBook[i].getId(), listBook[i].getName().c_str(),
                   listBook[i].getAuthor().c_str(), listBook[i].getStock(), listBook[i].getRating(), listBook[i].getCategory().getName().c_str());
        }
        cout << endl;
        return true;
    } else {
        cout << endl;
        return false;
    }
}

void LibrarySystem::displayBooks() {
    if (listBook.size() == 0) {
        cout << "There is no data in the list" << endl;
    } else {
        printf("%-10s | %-10s | %-10s | %-10s | %-10s | %-10s |\n", "ID", "Name", "Author", "Stock", "Rating", "Category");
        for (int i = 0; i < listBook.size(); i++) {
            Category c = listBook[i].getCategory();
            printf("%-10d | %-10s | %-10s | %-10d | %-10d | %-10s |\n", listBook[i].getId(), listBook[i].getName().c_str(),
                   listBook[i].getAuthor().c_str(), listBook[i].getStock(), listBook[i].getRating(), c.getName().c_str());
        }
    }
}

void LibrarySystem::displayBorrowedBooks() {

    bool borrowed = false;
    cout << "List of Borrowed Books\n"
            "=======================\n";

    printf("%-30s | %-10s |\n","Book Name", "Book ID");
    for (int i = 0; i < listTransaction.size(); i++) {
        Transaction t = listTransaction[i];

        //if book has not been returned
        if (t.getStatus() == "borrowed") {
            printf("-%30s | %-10d |\n", t.getBook().getName().c_str(), t.getBook().getId());
            borrowed = true;
        }
    }

    if (borrowed == false){
        cout << "\nNULL" << endl;
    }
}

void LibrarySystem::displayTopMonthlyBooks(string date) {
    vector<pair<int,string> >  topBooksList;
    Transaction t = listTransaction.back();
    bool contains = false;
    string bookName;
    int index,counter = 2;
    printf("%-30s | %-15s |\n","Book Name","Amount Borrowed");

    while(t.getDate() == date.substr(0,7)){

        bookName = t.getBook().getName();
        for (int i = 0;i < topBooksList.size(); i++){

            if (topBooksList[i].second == bookName) {
                index = i;
                contains = true;
            }
        }

        if (contains == false){
            topBooksList.push_back(make_pair(1,bookName));
        }

        else{
            topBooksList[index].first += 1;

        }

        t = listTransaction[listTransaction.size()-counter];
        counter++;
    }

    sort(topBooksList.begin(),topBooksList.end());

    for (int j = 0; j < 10;j++){

        printf("%-30s | %-10d", topBooksList[j].second.c_str(), topBooksList[j].first);
    }

}

// -- Category operations --

int LibrarySystem::addCategory(Category c) {
    listCategory.push_back(c);
    int size = listCategory.size();
    return size-1;
}

Category LibrarySystem::getCategory(int position) {
    return listCategory[position];
}

void LibrarySystem::removeCategory(int position) {
    listCategory.erase(listCategory.begin() + position);
}

void LibrarySystem::displayCategories() {

    if (listCategory.size() == 0) {
        cout << "There is no data in the list" << endl;
    } else {
        printf("%-20s | %-20s |\n", "ID", "Name");
        for (int i = 0; i < listCategory.size(); i++) {
            printf("%-20d | %-20s |\n", listCategory[i].getId(), listCategory[i].getName().c_str());
        }
    }
}

void LibrarySystem::updateCategory(int position, Category c) {
    listCategory[position].setName(c.getName());
}

bool LibrarySystem::searchCategory() {
    string key;

    bool found = false;
    vector<int> listFound;

    cout << "Input category name >>";
    cin >> key;

    for (int i = 0; i < listCategory.size(); ++i) {
        if (listCategory[i].getName() == key) {
            found = true;
            listFound.push_back(i);
        }
    }

    if (found) {
        printf("%-20s | %-20s |\n", "ID", "Name");
        for (int j = 0; j < listFound.size(); ++j) {
            int i = listFound[j];
            printf("%-20d | %-20s |\n", listCategory[i].getId(), listCategory[i].getName().c_str());
        }
        cout << endl;
        return true;
    } else {
        cout << endl;
        return false;
    }
}

int LibrarySystem::searchCategory(int id) {
    for (int i = 0; i < listCategory.size(); ++i) {
        if (listCategory[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

// -- Transaction operations --
void LibrarySystem::addTransaction(Transaction t) {
    listTransaction.push_back(t);
}

void LibrarySystem::viewTodaysTransactions(string date) {

    int counter = 2;
    Transaction t = listTransaction.back();

    printf("%-10s | %-30s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
    while (t.getDate() == date){
        printf("%-10s | %-30s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
               t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        t = listTransaction[listTransaction.size()-counter];
        counter++;
    }
}

void LibrarySystem::viewMonthlyTransactions(string date) {

    int counter = 2;
    Transaction t = listTransaction.back();

    printf("%-10s | %-30s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
    //takes only the year and the month
    while (t.getDate() == date.substr(0,7)){
        printf("%-10s | %-30s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
               t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        t = listTransaction[listTransaction.size()-counter];
        counter++;
    }
}
void LibrarySystem::viewAllTransactions() {
    if(listTransaction.size() == 0){
        cout << "There are no transactions in the list." << endl;
    }

    else{
        printf("%-10s | %-10s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
        for (int i = 0; i < listTransaction.size(); i++) {
            Transaction t = listTransaction[i];
            printf("%-10s | %-10s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
                    t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        }

    }

}

void LibrarySystem::testing(int a) {
    cout << "testing something" << endl;

}

void testfunc2() {
    cout << 'h';
}

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



