//
// Created by Hengky Sanjaya on 5/15/2019.
//
#include <chrono>
#include <ctime>
#include "library_system.h"
#include <windows.h>   // WinApi header ( HANDLE = to set color )
#include "setup_variables.h";

LibrarySystem::LibrarySystem() = default;

void LibrarySystem::WriteWithColor(string message, char color) {
//0 = Black	8 = Gray
//1 = Blue	9 = Light Blue
//2 = Green a = Light Green
//3 = Aqua	b = Light Aqua
//4 = Red	c = Light Red
//5 = Purple	d = Light Purple
//6 = Yellow	e = Light Yellow
//7 = White	f = Bright White
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, color);
    cout << message << endl;

    // reset to white textcolor
    SetConsoleTextAttribute(hConsole, 7);
}

void LibrarySystem::SetTextColor(char color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void LibrarySystem::ResetTextColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // reset to white textcolor
    SetConsoleTextAttribute(hConsole, 7);
}

string LibrarySystem::toLower(string text) {
    string result = "";
    for (int i = 0; i < text.length(); i++) {
        result += tolower(text[i]);
    }
    return result;
}

bool LibrarySystem::IsUsernameExist(string username) {
    for (User u : listUser) {
        if (u.getUsername() == username) {
            return true;
        }
    }
    return false;
}

User LibrarySystem::getCurrentUser() {
    return currentUser;
}

void LibrarySystem::setCurrentUser(User u) {
    this->currentUser = u;
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
}

vector<User> LibrarySystem::getListUser() {
    return listUser;
}

// -- Login --
bool LibrarySystem::doLogin(string username, string password, User &u) {
    for (User cur : listUser) {
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
         << "3. Category" << endl
         << ">>";

    cin >> suboption_book_search;

    if (suboption_book_search == 1) {
        cout << "Input book name >>";
    } else if (suboption_book_search == 2) {
        cout << "Input Author name >>";
    } else if (suboption_book_search == 3) {
        cout << "Input Category name >>";
    }

    cin.ignore();
    getline(cin, key);
//    cin >> key;
    key = toLower(key);

    bool found = false;
    vector<int> listFound;

    for (int i = 0; i < listBook.size(); ++i) {
        if (suboption_book_search == 1) {
            if (toLower(listBook[i].getName()) == key) {
                found = true;
                listFound.push_back(i);
            }
        } else if (suboption_book_search == 2) {
            if (toLower(listBook[i].getAuthor()) == key) {
                found = true;
                listFound.push_back(i);
            }
        } else if (suboption_book_search == 3) {
            if (toLower(listBook[i].getCategory().getName()) == key) {
                found = true;
                listFound.push_back(i);
            }
        }
    }

    if (found) {
        SetTextColor(COLOR_TABLE); // light yellow


        cout << endl;
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-40s | %-20s | %-10s | %-10s | %-6s |\n", "ID", "Name", "Author", "Stock", "Category",
               "Rating");
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        for (int i : listFound) {
            printf("| %-5d | %-40s | %-20s | %-10d | %-10s | %-6d |\n", listBook[i].getId(),
                   listBook[i].getName().c_str(),
                   listBook[i].getAuthor().c_str(), listBook[i].getStock(), listBook[i].getCategory().getName().c_str(),
                   listBook[i].getRating());
        }
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        cout << " Found " << listFound.size() << " of " << listBook.size() << endl;
        ResetTextColor();
        cout << endl;
        return true;
    } else {
        cout << endl;
        return false;
    }
}

void LibrarySystem::displayBooks() {
    if (listBook.empty()) {
        cout << "There is no data in the list" << endl;
    } else {
        SetTextColor(COLOR_TABLE); // light yellow

        printf(" ------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-40s | %-20s | %-10s | %-10s | %-6s |\n", "ID", "Name", "Author", "Stock", "Category",
               "Rating");
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        for (Book &i : listBook) {
            Category c = i.getCategory();
            printf("| %-5d | %-40s | %-20s | %-10d | %-10s | %-6d |\n", i.getId(), i.getName().c_str(),
                   i.getAuthor().c_str(), i.getStock(), c.getName().c_str(), i.getRating());
        }
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        cout << " Total data " << listBook.size() << endl;
        ResetTextColor();
    }
}

void LibrarySystem::displayBorrowedBooks() {

    bool borrowed = false;
    SetTextColor(COLOR_TABLE); // yellow
    cout << "List of Borrowed Books\n"
            "=======================\n";

    printf("%-30s | %-10s |\n", "Book Name", "Book ID");
    printf("---------------------------------------------");
    for (Transaction t : listTransaction) {
        //if book has not been returned
        if (t.getStatus() == "borrowed") {
            printf("%-30s | %-10d |\n", t.getBook().getName().c_str(), t.getBook().getId());
            borrowed = true;
        }
    }

    if (!borrowed) {
        cout << "\nNULL" << endl;
    }

    ResetTextColor();
}

void LibrarySystem::displayBorrowedBooks(User u) {

    bool borrowed = false;
    SetTextColor(COLOR_TABLE); // yellow
    cout << "List of Borrowed Books\n"
            "=======================\n";

    printf("%-10s | %-30s |\n", "Book ID", "Book Name");
    printf("---------------------------------------------\n");
    for (Transaction t : listTransaction) {
        //if book has not been returned
        if (t.getStatus() == "borrowed" && t.getUser().getUsername() == u.getUsername()) {
            printf("%-10d | %-30s |\n", t.getBook().getId(), t.getBook().getName().c_str());
            borrowed = true;
        }
    }

    if (!borrowed) {
        cout << "\nNULL" << endl;
    }
    ResetTextColor();
}


void LibrarySystem::displayTopBorrowedBooks(string date, int option) {

    if (listTransaction.empty()) {
        cout << "There are no existing transactions" << endl;
        return;
    }

    string condition;
    vector<pair<int, string> > topBooksList;
    Transaction t = listTransaction.back();
    bool contains = false;
    string bookName;
    int index, counter = 2, startSubStr, endSubStr;
    if (option == 1) {
        condition = date.substr(0, 7);
        startSubStr = 0;
        endSubStr = 7;
        cout << "                       Top 10 Most Borrowed Books This Month" << endl << endl;
    } else if (option == 2) {
        condition = date.substr(0, 3);
        startSubStr = 0;
        endSubStr = 3;
        cout << "                       Top 10 Most Borrowed Books This Year" << endl << endl;
    } else if (option == 3) {
        condition = date.substr(4, 0);
        startSubStr = 4;
        endSubStr = 0;
        cout << "                       Top 10 Most Borrowed Books Of All Time" << endl << endl;
    }
    printf("%-30s | %-15s |\n", "Book Name", "Amount Borrowed");

    while (t.getDate().substr(startSubStr, endSubStr) == condition) {

        bookName = t.getBook().getName();
        for (int i = 0; i < topBooksList.size(); i++) {

            if (topBooksList[i].second == bookName) {
                index = i;
                contains = true;
            }
        }

        if (!contains) {
            topBooksList.push_back(make_pair(1, bookName));
        } else {
            topBooksList[index].first += 1;
            contains = false;
        }

        t = listTransaction[listTransaction.size() - counter];
        counter++;
    }

    if (topBooksList.empty()) {
        cout << "No books have been borrowed. " << endl;
        return;
    }
    sort(topBooksList.begin(), topBooksList.end());

    for (int j = 0; j < 10; j++) {
        printf("%-30s | %-10d |\n", topBooksList[j].second.c_str(), topBooksList[j].first);
    }

}

// only displays books with more than 10 reads(?)
void LibrarySystem::displayTopRatedBooks(string date, int option) {

    if (listTransaction.empty()) {
        cout << "There are no existing transactions" << endl;
        return;
    }

    vector<pair<float, string> > ratedBookslist;
    vector<pair<int, Book> > topBooksList;

    Transaction t = listTransaction.back();
    bool contains = false;
    Book book;
    int index, counter = 2, startSubStr, endSubStr;
    string condition;
    if (option == 1) {
        condition = date.substr(0, 7);
        startSubStr = 0;
        endSubStr = 7;
        cout << "                       Top 10 Highest Rated Books This Month" << endl << endl;
    } else if (option == 2) {
        condition = date.substr(0, 3);
        startSubStr = 0;
        endSubStr = 3;
        cout << "                       Top 10 Highest Rated Books This Year" << endl << endl;
    } else if (option == 3) {
        condition = date.substr(4, 0);
        startSubStr = 4;
        endSubStr = 0;
        cout << "                       Top 10 Highest Rated Books Of All Time" << endl << endl;
    }
    printf("%-30s | %-10s |\n", "Book Name", "Rating");

    while (t.getDate().substr(startSubStr, endSubStr) == condition) {

        book = t.getBook();
        for (int i = 0; i < topBooksList.size(); i++) {

            if (topBooksList[i].second.getName() == book.getName()) {
                index = i;
                contains = true;
            }
        }

        if (contains == false) {
            topBooksList.push_back(make_pair(1, book));
        } else {
            topBooksList[index].first += 1;
            if (topBooksList[index].first >= 10) {
                ratedBookslist.push_back(
                        make_pair(topBooksList[index].second.getRating(), topBooksList[index].second.getName()));
            }
            contains = false;
        }

        t = listTransaction[listTransaction.size() - counter];
        counter++;
    }
    if (ratedBookslist.empty()) {
        cout << "No books have been borrowed or has not been rated 10 times. " << endl;
        return;
    }
    sort(ratedBookslist.begin(), ratedBookslist.end());
    for (int j = 0; j < 10; j++) {
        printf("%-30s | %10f", ratedBookslist[j].second.c_str(), ratedBookslist[j].first);
    }

}

// -- Category operations --

int LibrarySystem::addCategory(Category c) {
    listCategory.push_back(c);
    int size = listCategory.size();
    return size - 1;
}

Category LibrarySystem::getCategory(int position) {
    return listCategory[position];
}

void LibrarySystem::removeCategory(int position) {
    listCategory.erase(listCategory.begin() + position);
}

void LibrarySystem::displayCategories() {

    if (listCategory.empty()) {
        cout << "There is no data in the list" << endl;
    } else {
        SetTextColor(COLOR_TABLE); // light yellow
        printf("-------------------------------------------");
        printf("%-20s | %-20s |\n", "ID", "Name");
        printf("-------------------------------------------");
        for (Category &i : listCategory) {
            printf("%-20d | %-20s |\n", i.getId(), i.getName().c_str());
        }
        printf("-------------------------------------------");
        ResetTextColor();
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

vector<Category> LibrarySystem::getListCategory() {
    return listCategory;
}

// -- Transaction operations --
void LibrarySystem::addTransaction(int bookPosition) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    Transaction t(currentUser, listBook[bookPosition], "borrowed", std::ctime(&now_time), "");
    listTransaction.push_back(t);
}

bool LibrarySystem::returnBook(int bookId) {
    for (Transaction t : listTransaction) {
        if (t.getUser().getUsername() == currentUser.getUsername() && t.getBook().getId() == bookId) {
            t.setStatus("returned");
            return true;
        }
    }
    return false;
}

void LibrarySystem::updateTransactionStatus(int bookposition) {

    for (int i = 0; i < listTransaction.size(); i++) {

        if (listTransaction[i].getBook().getName() == listBook[bookposition].getName() &&
            currentUser.getUsername() == listTransaction[i].getUser().getUsername()) {

            listTransaction[i].setStatus("returned");
            listTransaction[i].getUser().addExp();

        }
    }

}

void LibrarySystem::viewTodaysTransactions(string date) {

    int counter = 2;
    Transaction t = listTransaction.back();

    printf("%-10s | %-30s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
    while (t.getDate() == date) {
        printf("%-10s | %-30s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
               t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        t = listTransaction[listTransaction.size() - counter];
        counter++;
    }
}

void LibrarySystem::viewMonthlyTransactions(string date) {

    int counter = 2;
    Transaction t = listTransaction.back();

    printf("%-10s | %-30s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
    //takes only the year and the month
    while (t.getDate() == date.substr(0, 7)) {
        printf("%-10s | %-30s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
               t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        t = listTransaction[listTransaction.size() - counter];
        counter++;
    }
}

void LibrarySystem::viewAllTransactions() {
    if (listTransaction.empty()) {
        cout << "There are no transactions in the list." << endl;
    } else {
        printf("%-10s | %-10s | %-10s | %-10s | %-50s |\n", "Username", "Book", "Status", "Date", "Review");
        for (Transaction t : listTransaction) {
            printf("%-10s | %-10s | %-10s | %-10d | %-50s |\n", t.getUser().getUsername().c_str(),
                   t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());

        }

    }

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



