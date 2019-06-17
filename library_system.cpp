//
// Created by Hengky Sanjaya on 5/15/2019.
//
#include <chrono>
#include <ctime>
#include "library_system.h"
#include <windows.h>   // WinApi header ( HANDLE = to set color )
#include <sstream>
#include "setup_variables.h"
#include <math.h>
#include "Helper/sort.cpp"

using namespace chrono;

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

vector<string> LibrarySystem::getUsersinFormat() {
    vector<string> result;

    for (int i = 0; i < listUser.size(); i++) {
        stringstream ss;
        ss << listUser[i].getName() << "," << listUser[i].getUsername() << "," << listUser[i].getPassword() << ","
           << listUser[i].getRole() << "\n";
        result.push_back(ss.str());
    }

    return result;
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
    listBook[position].setCategory(b.getCategory());
}

int LibrarySystem::searchBook(int id) {
    if (id <= listBook.size()) {
        auto current = listBook[id - 1];

        int nBorrowed = 0;
        for (Transaction t : listTransaction) {
            if (t.getBook().getId() == current.getId() && t.getStatus() == "borrowed") {
                nBorrowed += 1;
            }
        }

        if ((current.getStock() - nBorrowed) == 0) {
            return -2;
        }

        return id - 1;
    }
    return -1;
}

bool LibrarySystem::searchBook() {
    string suboption_book_search;
    string key;
    SetTextColor(COLOR_OPTIONS);
    bool correctInput = false;
    while (correctInput == false) {


        cout << "Search book by : " << endl
             << "1. Name          " << endl
             << "2. Author        " << endl
             << "3. Category      " << endl
             << ">>";
        ResetTextColor();

        cin >> suboption_book_search;

        if (suboption_book_search == "1") {
            correctInput = true;
            cout << "Input book name >>";
        } else if (suboption_book_search == "2") {
            correctInput = true;
            cout << "Input Author name >>";
        } else if (suboption_book_search == "3") {
            correctInput = true;
            cout << "Input Category name >>";
        } else {
            WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
            ResetTextColor();
        }
    }
    cin.ignore();
    getline(cin, key);
//    cin >> key;
    key = toLower(key);
    int keyLength = key.size();

    bool found = false;
    vector<int> listFound;

    for (int i = 0; i < listBook.size(); ++i) {
        if (suboption_book_search == "1") {
            if (toLower(listBook[i].getName()).substr(0, keyLength) == toLower(key).substr(0, keyLength)) {
                found = true;
                listFound.push_back(i);
            }
        } else if (suboption_book_search == "2") {
            if (toLower(listBook[i].getAuthor()).substr(0, keyLength) == toLower(key).substr(0, keyLength)) {
                found = true;
                listFound.push_back(i);
            }
        } else if (suboption_book_search == "3") {
            if (toLower(listBook[i].getCategory().getName()) == toLower(key)) {
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
            int nBorrowed = 0;
            for (Transaction t : listTransaction) {
                if (t.getBook().getId() == listBook[i].getId() && t.getStatus() == "borrowed") {
                    nBorrowed += 1;
                }
            }
            int stock = listBook[i].getStock() - nBorrowed;

            printf("| %-5d | %-40s | %-20s | %-10d | %-10s | %-6d |\n", listBook[i].getId(),
                   listBook[i].getName().c_str(),
                   listBook[i].getAuthor().c_str(), stock, listBook[i].getCategory().getName().c_str(),
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

    string sortby_input, sortby;
    bool valInp = true;
    if (listBook.empty()) {
        cout << "There is no data in the list" << endl;
        return;
    } else {
        do {
            SetTextColor(COLOR_OPTIONS);
            cout << "Sort book by : \n"
                    "1. Name        \n"
                    "2. Author      \n"
                    "3. Stock       \n"
                    ">>" << endl;
            ResetTextColor();

            cin >> sortby_input;

            SetTextColor(COLOR_TABLE); // light yellow

            if (sortby_input == "1") {
                sortby = "name";
                valInp = true;
            } else if (sortby_input == "2") {
                sortby = "author";
                valInp = true;
            } else if (sortby_input == "3") {
                sortby = "stock";
                valInp = true;
            } else {
                WriteWithColor("\nWrong Input\n", COLOR_WARNING_MESSAGE);
                valInp = false;
            }
        } while (valInp == false);
        Sorting<vector<Book>> s;

        vector<Book> book_list = listBook;
        auto start = system_clock::now();
        s.mergeSort(book_list, 0, book_list.size() - 1, sortby);
        auto end = system_clock::now();
        auto elapsed = double(duration_cast<milliseconds>(end - start).count());
        auto nano = double(duration_cast<nanoseconds>(end - start).count());

        printf(" ------------------------------------------------------------------------------------------------------------\n");
        printf("| %-5s | %-40s | %-20s | %-10s | %-10s | %-6s |\n", "ID", "Name", "Author", "Stock", "Category",
               "Rating");
        printf(" ------------------------------------------------------------------------------------------------------------\n");


        for (Book &i : book_list) {
            int nBorrowed = 0;
            int nRating = 0, totalRating = 0;
            for (Transaction t : listTransaction) {
                if (t.getBook().getId() == i.getId() && t.getStatus() == "borrowed") {
                    nBorrowed += 1;
                }

                if (t.getBook().getId() == i.getId() && t.getRating() != 0) {
                    totalRating += t.getRating();
                    nRating++;
                }
            }

            float rating = 0;
            if (nRating != 0) {
                rating = (float) totalRating / nRating;
            }
            int stock = i.getStock() - nBorrowed;

            Category c = i.getCategory();
            printf("| %-5d | %-40s | %-20s | %-10d | %-10s | %-6.2f |\n", i.getId(), i.getName().c_str(),
                   i.getAuthor().c_str(), stock, c.getName().c_str(),
                   rating);
        }
        printf(" ------------------------------------------------------------------------------------------------------------\n");
        cout << " Total data " << listBook.size() << endl;
        cout << " Merge sort time taken : " << elapsed << " ms  | " << nano << " ns" << endl << endl;

        ResetTextColor();
    }
}

void LibrarySystem::displayBorrowedBooks() {

    bool borrowed = false;
    SetTextColor(COLOR_TABLE); // yellow
    cout << "List of Borrowed Books\n"
            "=======================\n\n";

    printf(" ------------------------------------------------------------\n");
    printf("| %-40s | %-15s |\n", "Book Name", "User");
    printf(" ------------------------------------------------------------\n");
    for (Transaction t : listTransaction) {
        //if book has not been returned
        if (t.getStatus() == "borrowed") {
            printf("| %-40s | %-15s |\n", t.getBook().getName().c_str(),
                   t.getUser().getName().c_str());
            borrowed = true;
        }
    }

    if (!borrowed) {
        cout << " NULL" << endl;
    }
    printf(" ------------------------------------------------------------\n\n");
    ResetTextColor();
}

void LibrarySystem::displayBorrowedBooks(User u) {

    bool borrowed = false;
    SetTextColor(COLOR_TABLE); // yellow
    cout << "List of Borrowed Books\n"
            "=======================\n\n";

    printf(" -------------------------------------------------------\n");
    printf("| %-10s | %-40s |\n", "Book ID", "Book Name");
    printf(" -------------------------------------------------------\n");
    for (Transaction t : listTransaction) {
        //if book has not been returned
        if (t.getStatus() == "borrowed" && t.getUser().getUsername() == u.getUsername()) {
            printf("| %-10d | %-40s |\n", t.getBook().getId(), t.getBook().getName().c_str());
            borrowed = true;
        }
    }

    if (!borrowed) {
        cout << " NULL" << endl;
    }
    printf(" -------------------------------------------------------\n\n");
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

// displays top rated books
void LibrarySystem::displayTopRatedBooks(string date, int option) {

    if (listTransaction.empty()) {
        cout << "There are no existing transactions" << endl;
        return;
    }
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
        }
        contains = false;


        t = listTransaction[listTransaction.size() - counter];
        counter++;
    }
    if (topBooksList.empty()) {
        cout << "No books have been borrowed. " << endl;
        return;
    }
//    sort(topBooksList.begin(), topBooksList.end());
    for (int j = 0; j < 10; j++) {
        printf("%-30s | %10f", topBooksList[j].second.getName().c_str(), topBooksList[j].first);
    }
// -- Category operations --

}

vector<string> LibrarySystem::getBooksInFormat() {
    vector<string> result;

    for (int i = 0; i < listBook.size(); i++) {
        stringstream ss;
        ss << listBook[i].getId() << "," << listBook[i].getName() << "," << listBook[i].getAuthor() << ","
           << listBook[i].getStock() << "," << listBook[i].getCategory().getId() << "," << listBook[i].getRating()
           << "\n";
        result.push_back(ss.str());
    }

    return result;
}

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

        Sorting<vector<Category>> s;

        vector<Category> category_list = listCategory;
        auto start = system_clock::now();
        s.mergeSort(category_list, 0, category_list.size() - 1, "name");
        auto end = system_clock::now();

        printf("  -------------------------------------------\n");
        printf("| %-20s | %-20s |\n", "ID", "Name");
        printf("  -------------------------------------------\n");
        for (Category &i : category_list) {
            printf("| %-20d | %-20s |\n", i.getId(), i.getName().c_str());
        }
        printf("  -------------------------------------------\n");
        auto elapsed = double(duration_cast<milliseconds>(end - start).count());
        auto nano = double(duration_cast<nanoseconds>(end - start).count());
        cout << "  Total items : " << category_list.size() << endl;
        cout << "  Merge sort time taken : " << elapsed << " ms  | " << nano << " ns" << endl << endl;
        ResetTextColor();
    }
}

vector<string> LibrarySystem::getCategoriesInFormat() {
    vector<string> result;

    for (int i = 0; i < listCategory.size(); i++) {
        stringstream ss;
        ss << listCategory[i].getId() << "," << listCategory[i].getName() << "\n";
        result.push_back(ss.str());
    }

    return result;
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

    key = toLower(key);
    for (int i = 0; i < listCategory.size(); ++i) {
        if (toLower(listCategory[i].getName()) == key) {
            found = true;
            listFound.push_back(i);
        }
    }

    if (found) {
        SetTextColor(COLOR_TABLE);
        printf("  -----------------------\n");
        printf("| %-20s | %-20s |\n", "ID", "Name");
        printf("  -----------------------\n");
        for (int j = 0; j < listFound.size(); ++j) {
            int i = listFound[j];
            printf("| %-20d | %-20s |\n", listCategory[i].getId(), listCategory[i].getName().c_str());
        }
        printf("  -----------------------\n");
        cout << "  Found " << listFound.size() << " of " << listCategory.size() << endl;
        ResetTextColor();
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

void LibrarySystem::viewBooksReview() {

    string inp = "";
    int id;
    int pos;
    bool valInp = false;
    bool found = searchBook();

    if (found) {
        while (valInp == false) {
            valInp = true;
            cout << "Input book id\n>> ";
            cin >> inp;
            cout << endl;

            for (int i = 0; i < inp.length(); i++) {
                if (!isdigit(inp[i])) {
                    valInp = false;
                }
            }
            if (valInp == false) {
                WriteWithColor("Please input a number.", COLOR_WARNING_MESSAGE);
            }
        }
    } else {
        WriteWithColor("Book not found\n", COLOR_WARNING_MESSAGE);
        return;
    }
    id = stoi(inp);
    pos = searchBook(id);
    if (pos == -1) {
        WriteWithColor("Sorry, book id not found", COLOR_WARNING_MESSAGE);
        return;
    }
    SetTextColor(COLOR_TABLE);
    printf("  -------------------------------------------------------------------------------------\n");
    printf("| %-40s | %-40s |\n", "Book Name", "Review");
    printf("  -------------------------------------------------------------------------------------\n");

    printf("| %-40s | %-40s |\n", listBook[pos].getName().c_str(), "");

    for (Transaction t : listTransaction) {
        if (t.getReview() != "" && t.getBook().getId() == listBook[pos].getId())
            printf("| %-40s | %-40s |\n", "", (t.getUser().getUsername() + " : " + t.getReview()).c_str());
    }

    printf("  -------------------------------------------------------------------------------------\n");
    ResetTextColor();
}

void LibrarySystem::viewHighestRatedBooks() {

    int i = 0;
    for (Book b : listBook) {
        int nRating = 0, totalRating = 0;
        for (Transaction t : listTransaction) {

            if (t.getBook().getId() == b.getId() && t.getRating() != 0) {
                totalRating += t.getRating();
                nRating++;
            }
        }

        float rating = 0;
        if (nRating != 0) {
            rating = (float) totalRating / nRating;
        }

        listBook[i].setRating(rating);
//        b.setRating(rating);
        i++;
    }

    auto list = listBook;
    sort(list.begin(), list.end(), [](Book const &a, Book const &b) -> bool {
        return a.getRating() > b.getRating();
    });

    SetTextColor(COLOR_TABLE);
    printf("  ------------------------------------------------------------------------------------------------------------\n");
    printf("| %-40s | %-20s | %-20s | %-20s |\n", "Book Name", "Author", "Category", "Rating");
    printf("  ------------------------------------------------------------------------------------------------------------\n");

    int n = 0;
    for (Book b : list) {
        if (b.getRating() == 0)break;
        n++;
        printf("| %-40s | %-20s | %-20s | %-20.2f |\n", b.getName().c_str(), b.getAuthor().c_str(),
               b.getCategory().getName().c_str(), b.getRating());
        if (n == 3) break;
    }
    printf("  ------------------------------------------------------------------------------------------------------------\n");
    cout << "  Found " << n << " of 3" << endl;
    ResetTextColor();
    cout << endl;
}

void LibrarySystem::viewHighestBorrowedBooks() {
    vector<pair<int, int>> list;
    for (Book b : listBook) {
        int nBorrowed = 0;
        for (Transaction t : listTransaction) {
            if (t.getBook().getId() == b.getId()) {
                nBorrowed++;
            }
        }
        pair<int, int> value;
        value.first = b.getId();
        value.second = nBorrowed;
        list.push_back(value);
    }

    SetTextColor(COLOR_TABLE);
    printf("  ------------------------------------------------------------------------------------------------------------\n");
    printf("| %-40s | %-20s | %-20s | %-20s |\n", "Book Name", "Author", "Category", "Amount");
    printf("  ------------------------------------------------------------------------------------------------------------\n");

    sort(list.begin(), list.end(), [](const pair<int, int> &a, const pair<int, int> &b) -> bool {
        return a.second > b.second;
    });

    int n = 0;
    for (auto l : list) {
        if (l.second == 0)break;
        n++;
        auto b = listBook[l.first - 1];
        printf("| %-40s | %-20s | %-20s | %-20d |\n", b.getName().c_str(), b.getAuthor().c_str(),
               b.getCategory().getName().c_str(), l.second);
        if (n == 3) break;
    }
    printf("  ------------------------------------------------------------------------------------------------------------\n");
    cout << "  Found " << n << " of 3" << endl;
    ResetTextColor();
    cout << endl;
}

vector<string> LibrarySystem::getTransactionsinFormat() {
    vector<string> result;

    for (int i = 0; i < listTransaction.size(); i++) {
        stringstream ss;
        ss << listTransaction[i].getUser().getUsername() << "," << listTransaction[i].getBook().getId() << ","
           << listTransaction[i].getStatus() << "," << listTransaction[i].getDate() << ","
           << listTransaction[i].getReview() << "," << listTransaction[i].getRating()
           << "\n";
        result.push_back(ss.str());
    }

    return result;
}

bool LibrarySystem::addTransaction(int bookPosition) {
//    auto now = std::chrono::system_clock::now();
//    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    time_t curr_time;
    tm *curr_tm;
    time(&curr_time);
    curr_tm = localtime(&curr_time);

    for (auto i : listTransaction) {
        if (i.getUser().getUsername() == currentUser.getUsername() &&
            i.getBook().getId() == listBook[bookPosition].getId() && i.getStatus() == "borrowed") {
            return false;
        }
    }

    char date_string[100];
    strftime(date_string, 50, "%d %B %Y", curr_tm);

    Transaction t(currentUser, listBook[bookPosition], "borrowed", date_string, "", 0);
    listTransaction.push_back(t);
    return true;
}

bool LibrarySystem::addTransaction(string username, int bookId, string status, string date, string review, int rating) {
    int userPos = 0;
    for (int i = 0; i < listUser.size(); ++i) {
        if (listUser[i].getUsername() == username) {
            userPos = i;
            break;
        }
    }

    int bookPos = 0;
    for (int j = 0; j < listBook.size(); ++j) {
        if (listBook[j].getId() == bookId) {
            bookPos = j;
            break;
        }
    }


    listTransaction.push_back(Transaction(listUser[userPos], listBook[bookPos], status, date, review, rating));
    return true;
}

bool LibrarySystem::returnBook(int bookId) {

    int i = 0;
    for (Transaction t : listTransaction) {
        if (t.getUser().getUsername() == currentUser.getUsername() && t.getBook().getId() == bookId &&
            t.getStatus() == "borrowed") {
//            t.setStatus("returned");
            listTransaction[i].setStatus("returned");

            string choice;
            cout << "Would you like to give your review of this book ? (Y/N)" << endl;
            cin >> choice;
            string review = "";
            if (choice == "Y" || choice == "y") {
                cout << "Enter your review >>" << endl;
                cin.ignore();
                getline(cin, review);
            }

            listTransaction[i].setReview(review);

            int rating;
            cout << "Enter rating (1-5) >>" << endl;
            cin >> rating;
            listTransaction[i].setRating(rating);

            cout << "Thank you" << endl;

            return true;
        }
        i++;
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
        SetTextColor(COLOR_TABLE);
        int n = 0;
        auto start = system_clock::now();
        printf("  --------------------------------------------------------------------------------------------------------------\n");
        printf("| %-10s | %-40s | %-10s | %-15s | %-20s |\n", "Username", "Book", "Status", "Date", "Review");
        printf("  --------------------------------------------------------------------------------------------------------------\n");
        for (Transaction t : listTransaction) {
            printf("| %-10s | %-40s | %-10s | %-15s | %-20s |\n", t.getUser().getUsername().c_str(),
                   t.getBook().getName().c_str(), t.getStatus().c_str(), t.getDate().c_str(), t.getReview().c_str());
            n++;
        }
        printf("  --------------------------------------------------------------------------------------------------------------\n");
        cout << "  Total items : " << n << endl << endl;
        auto end = system_clock::now();
        auto elapsed = double(duration_cast<milliseconds>(end - start).count());
        auto nano = double(duration_cast<nanoseconds>(end - start).count());
        cout << "  Time taken : " << elapsed << " ms  | " << nano << " ns" << endl << endl;
        ResetTextColor();
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



