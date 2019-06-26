//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system_ui.h"
#include "setup_variables.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <chrono>
#include <stdio.h>
#include "DataStructure/btree.cpp"

#define ENTER 13
#define TAB 9
#define BKSP 8

using namespace chrono;

// function to set passwordchar '*'
string LibrarySystemUI::enterPassword() {
    int charCount = 0;
    char ch, password[100];
    bool passwordLoop = true;
    while (passwordLoop == true) {
        ch = getch();

        if (ch == ENTER || ch == TAB) {
            password[charCount] = '\0';
            break;
        } else if (ch == BKSP) {
            if (charCount > 0) {
                charCount--;
                printf("\b \b");
            }
        } else {
            password[charCount] = ch;
            charCount++;
            printf("* \b");
        }
    }
    cout << endl;

    return password;

}

// function to split string by delimiter
vector<string> LibrarySystemUI::split(string text, char delimiter) {
    int length = text.length();
    vector<string> result;

    string temp;
    for (int i = 0; i < length; i++) {
        if (text[i] == delimiter) {
            result.push_back(temp);
            temp = "";
        } else if (i == (length - 1)) {
            temp += text[i];
            result.push_back(temp);
            temp = "";
        } else {
            temp += text[i];
        }
    }

    return result;
}

// function to read data from file
vector<vector<string>> LibrarySystemUI::readFile(string filename) {
    string line;
    ifstream file;
    file.open("../database/" + filename);

    vector<vector<string>> list;
    if (!file) {
        cout << "cannot open the file " << endl;
    } else {
        while (file) {
            getline(file, line);

            if (line != "") {
                vector<string> test = split(line, ',');
                list.push_back(test);
            }
        }
    }

    file.close();
    return list;
}

// function to write data to file
void LibrarySystemUI::writeFile(string filename, vector<string> list) {
    ofstream file;
    file.open("../database/" + filename, ios::trunc);
    if (file.is_open()) {
        for (int i = 0; i < list.size(); i++) {
            file << list[i];
        }
    }

    file.close();
}

// function to display add category ui
int LibrarySystemUI::addCategoryUI() {
    cout << "-- Insert category --" << endl;

    string c_name;
    cout << "category's name >>";
    cin >> c_name;

    int index = ls.addCategory(Category(c_name));

    ls.WriteWithColor("~ Category added successfully ~", COLOR_SUCCESS_MESSAGE);
    cout << endl;
    return index;
}

// function to run ui
void LibrarySystemUI::run() {
    vector<vector<string>> dataCategory = readFile("category.csv");
    for (auto i : dataCategory) {
        ls.addCategory((Category(i[1])));
    }

    vector<vector<string>> dataBook = readFile("book.csv");
    for (auto i : dataBook) {
        auto b = Book(i[1], i[2], stoi(i[3]), ls.getCategory(stoi(i[4]) - 1));
        b.setRating(stoi(i[5]));
        ls.addBook(b);
    }

//    ls.addBook(Book("How to be Invisible: Lyrics", "Kate Bush", 10, ls.getListCategory()[1]));
//    ls.addBook(Book("The Only Business", "Laura Brown", 100, ls.getListCategory()[0]));
//    ls.addBook(Book("10 Steps to Successful Budgeting", "Lianabel Oliver", 200, ls.getListCategory()[0]));
//    ls.addBook(Book("Education and the Commercial Mindset", "Samuel E. Abrams", 350, ls.getListCategory()[5]));


    vector<vector<string>> dataUser = readFile("user.csv");
    for (auto i : dataUser) {
        ls.addUser(User(i[0], i[1], i[2], i[3]));
    }
//    ls.addUser(User("test", "test", "test", "A"));
//    ls.addUser(User("coba", "coba", "coba", "U"));

    vector<vector<string>> dataTransaction = readFile("transaction.csv");
    for (auto i : dataTransaction) {
        ls.addTransaction(i[0], stoi(i[1]), i[2], i[3], i[4], i[5], stoi(i[6]));
    }
//    ls.setCurrentUser(ls.getListUser()[0]);
//    ls.addTransaction(1);
//    writeFile("transaction.csv", ls.getTransactionsinFormat());

    string option;

    while (true) {
        string title = "=========================================\n"
                       "=         Welcome to HR Library         =\n"
                       "=========================================\n";
        ls.WriteWithColor(title, 9);

        ls.WriteWithColor("1. Login    \n"
                          "2. Register \n"
                          //"3. Test BTree \n"
                          "3. Exit     \n"
                          ">>", COLOR_OPTIONS);

        cin >> option;
        // login
        if (option == "1") {
            string username;
            string password;
            cout << "please enter your :" << endl;
            cout << "username >>";
            cin >> username;
            cout << "password >>";

            password = enterPassword();

            User u;
            bool login = ls.doLogin(username, password, u);
            if (login) {
                ls.setCurrentUser(u);
                ls.WriteWithColor("~ Login Success ~", COLOR_SUCCESS_MESSAGE);
                if (u.getRole() == "A") {
                    adminPage(u);
                } else if (u.getRole() == "U") {
                    userPage(u);
                }
            } else {
                ls.WriteWithColor("Username or password incorrect", COLOR_WARNING_MESSAGE); // pink
            }
        }
            // register
        else if (option == "2") {
            string name, username, password, confirm_password, role;

            cout << "-- Add New User --" << endl;

            cout << "name >>";
            cin >> name;

            while (true) {
                cout << "username >> ";
                cin >> username;

                if (ls.IsUsernameExist(username)) {
                    ls.WriteWithColor("Username has already been taken", COLOR_WARNING_MESSAGE);
                } else {
                    break;
                }
            }

            while (true) {
                cout << "password >> ";
                password = enterPassword();
                cout << "confirm password >>";
                confirm_password = enterPassword();

                if (confirm_password != password) {
                    ls.WriteWithColor("Passwords are not the same", COLOR_WARNING_MESSAGE);
                } else {
                    break;
                }
            }

            ls.addUser(User(name, username, password, "U"));

            ls.WriteWithColor("Register success", COLOR_SUCCESS_MESSAGE);
        }
            // exit
        else if (option == "3") {
            writeFile("book.csv", ls.getBooksInFormat());
            writeFile("category.csv", ls.getCategoriesInFormat());
            writeFile("user.csv", ls.getUsersinFormat());
            writeFile("transaction.csv", ls.getTransactionsinFormat());
            break;
        } else {
            ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
        }
        cout << endl;
    }
}

// function to display userpage ui
void LibrarySystemUI::userPage(User currentUser) {

    string option;
    int topBookoption, timeSpan;
    string year, month, day, date;
    time_t now = time(0);
    ls.compareReturnDates(now);
    while (true) {
        cout << endl;
        ls.WriteWithColor("Welcome " + currentUser.getName() + " (User)\n"
                                                               "1. Borrow book                          \n"
                                                               "2. Return Book                          \n"
                                                               //"3. View Top Books              \n"
                                                               "3. View All Books                       \n"
                                                               "4. View Top 3 Books by Rating           \n"
                                                               "5. View Top 3 Books by Amount borrowed  \n"
                                                               "0. Logout                               \n"
                                                               ">>", COLOR_OPTIONS);

        cin >> option;

        // borrow book

        if (option == "1") {
            int bookid;
            bool found = ls.searchBook();
            if (found == false) {
                ls.WriteWithColor("There is no data in the list", COLOR_WARNING_MESSAGE);
            } else {
                cout << "-- Borrow book --" << endl
                     << "Input book's id >>";
                cin >> bookid;

                auto start = system_clock::now();
                int pos = ls.searchBook(bookid);
                auto end = system_clock::now();
                auto elapsed = double(duration_cast<milliseconds>(end - start).count());
                auto nano = double(duration_cast<nanoseconds>(end - start).count());

                if (pos == -1) {
                    ls.WriteWithColor("Sorry, book id not found", COLOR_WARNING_MESSAGE);
                } else if (pos == -2) {
                    ls.WriteWithColor("Sorry, book out of stock", COLOR_WARNING_MESSAGE);
                } else {

                    bool res = ls.addTransaction(pos);

                    if (res) {
                        cout << " Hash search time taken : " << elapsed << " ms  | " << nano << " ns" << endl;
                        ls.WriteWithColor("~ Transaction success ~", COLOR_SUCCESS_MESSAGE);
                    } else {
                        ls.WriteWithColor("Sorry, You have already borrowed this book", COLOR_WARNING_MESSAGE);
                    }
                }
            }
        }
            // return book
        else if (option == "2") {

            bool valInp = false;
            cout << "- Return Book -" << endl;

            int bookId;
            while (valInp == false) {

                ls.displayBorrowedBooks(currentUser);
                cout << "Input Book Id you want to return >>";


                cin >> bookId;

                if (!cin.fail()) {
                    valInp = true;
                } else {
                    ls.WriteWithColor("\nPlease input a number\n", COLOR_WARNING_MESSAGE);
                    cin.clear();
                    cin.ignore(256, '\n');
                }
            }
            if (ls.returnBook(bookId)) {
                ls.WriteWithColor("Return book success", COLOR_SUCCESS_MESSAGE);
                currentUser.addExp();
            } else {
                ls.WriteWithColor("Sorry, You dont borrow this book", COLOR_WARNING_MESSAGE);
            }
        }
            // view all books
//        else if (option == 3) {
//
//            time_t theTime = time(NULL);
//            struct tm *currTime = localtime(&theTime);
//
//            day = to_string(currTime->tm_mday);
//            month = to_string(currTime->tm_mon + 1);
//            year = to_string(currTime->tm_year + 1900);
//
//            date = year + "-" + month + "-" + day;
//
//            ls.WriteWithColor("View By:\n"
//                              "1. Rating         \n"
//                              "2. Amount Borrowed\n"
//                              ">>", COLOR_OPTIONS);
//
//            cin >> topBookoption;
//
//            ls.WriteWithColor("Time Span: \n"
//                              "1. This Month \n"
//                              "2. This Year  \n"
//                              "3. All Time   \n"
//                              ">>", COLOR_OPTIONS);
//
//            cin >> timeSpan;
//
//            if (topBookoption == 1) {
//                ls.displayTopRatedBooks(date, timeSpan);
//            } else if (topBookoption == 2) {
//                ls.displayTopBorrowedBooks(date, timeSpan);
//            }
//
//
//        }
        else if (option == "3") {
            cout << "-- View all books --" << endl;
            ls.displayBooks();
        }
            // view highest rated books
        else if (option == "4") {
            ls.viewHighestRatedBooks();
        }
            // view highest borrowedbooks
        else if (option == "5") {
            ls.viewHighestBorrowedBooks();
        }
            // exit
        else if (option == "0") {
            break;
        }
            // wrong input
        else {
            ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
        }
    }
    }
// function to display admin page ui
    void LibrarySystemUI::adminPage(User currentUser) {
        string option;
        while (true) {
            cout << endl;
            ls.WriteWithColor("Welcome " + currentUser.getName() + " (admin)\n"
                                                                   "1. Master Data                          \n"
                                                                   "2. View Transaction                     \n"
                                                                   "3. View Borrowed Books                  \n"
                                                                   "4. View Book's Review                   \n"
                                                                   "5. View Top 3 Books by Rating           \n"
                                                                   "6. View Top 3 Books by Amount borrowed  \n"
                                                                   "7. Logout                               \n"
                                                                   ">>", COLOR_OPTIONS);

            cin >> option;
            // master data
            if (option == "1") {
                bool valInp = false;
                string suboption_master_data;
                ls.SetTextColor(COLOR_OPTIONS);
                while (valInp == false) {
                    cout << "1. Book     " << endl
                         << "2. Category " << endl
                         //<< "3. User     " << endl
                         << ">>";
                    ls.ResetTextColor();
                    cin >> suboption_master_data;

                    if (suboption_master_data != "1" && suboption_master_data != "2") {
                        ls.WriteWithColor("\nWrong Input\n", COLOR_WARNING_MESSAGE);
                    } else {
                        break;
                    }
                }
                // book
                if (suboption_master_data == "1") {
                    while (true) {
                        string suboption_book;
                        ls.SetTextColor(COLOR_OPTIONS);
                        cout << "Book CRUD       " << endl
                             << "1. Insert       " << endl
                             << "2. Update       " << endl
                             << "3. Delete       " << endl
                             << "4. Search       " << endl
                             << "5. View all     " << endl
                             << "6. Back to menu " << endl
                             << ">>";
                        ls.ResetTextColor();
                        cin >> suboption_book;
                        // insert book
                        if (suboption_book == "1") {
                            cout << "-- Insert book --" << endl;
                            string b_name, b_author, category_option;
                            int b_stock;

                            cout << "book's name >>";
                            cin >> b_name;

                            cout << "book's author >>";
                            cin >> b_author;

                            cout << "book's stock >>";
                            cin >> b_stock;

                            int pos;
                            while (true) {
                                cout << "Browse category or insert new [B,I]?" << endl;
                                cin >> category_option;


                                if (category_option == "b" || category_option == "B") {
                                    bool re = ls.searchCategory();

                                    if (re == false) {
                                        cout << "There is no data found in category list" << endl;
                                    } else {
                                        cout << "Please input category's Id >>";
                                        int categoryId;
                                        cin >> categoryId;

                                        pos = ls.searchCategory(categoryId);

                                        if (pos != -1) {
                                            break;
                                        } else {
                                            cout << "CategoryId not found" << endl;
                                        }
                                    }
                                } else if (category_option == "i" || category_option == "I") {
                                    pos = addCategoryUI();
                                    break;
                                }
                            }

//                        cout << "position" << pos << endl;
                            Category c = ls.getCategory(pos);
//                        cout << "category name" << c.getName() << endl;

                            Book b = Book(b_name, b_author, b_stock, c);
//                        cout << "category name2 " << b.getCategory().getName() << endl;
                            ls.addBook(b);

                            ls.WriteWithColor("~ Book added successfully ~", COLOR_SUCCESS_MESSAGE);
                            cout << endl;
                        }
                            // update book
                        else if (suboption_book == "2") {
                            cout << "-- Update book --" << endl;
                            bool re = ls.searchBook();

                            if (re == false) {
                                cout << "There is no data found" << endl;
                                continue;
                            }

                            cout << "Please input book's Id >>";
                            int bookId;
                            cin >> bookId;

                            int pos_book = ls.searchBook(bookId);
                            if (pos_book != -1) {

                                string b_name, b_author, category_option;
                                int b_stock;

                                cout << "book's name >>";
                                cin >> b_name;

                                cout << "book's author >>";
                                cin >> b_author;

                                cout << "book's stock >>";
                                cin >> b_stock;

                                int pos;
                                while (true) {
                                    cout << "Browse category or insert new [B,I]?" << endl;
                                    cin >> category_option;


                                    if (category_option == "b" || category_option == "B") {
                                        bool re = ls.searchCategory();

                                        if (re == false) {
                                            cout << "There is no data found in category list" << endl;
                                        } else {
                                            cout << "Please input category's Id >>";
                                            int categoryId;
                                            cin >> categoryId;

                                            pos = ls.searchCategory(categoryId);

                                            if (pos != -1) {
                                                break;
                                            } else {
                                                cout << "CategoryId not found" << endl;
                                            }
                                        }
                                    } else if (category_option == "i" || category_option == "I") {
                                        pos = addCategoryUI();
                                        break;
                                    }
                                }

                                Category c = ls.getCategory(pos);
                                ls.updateBook(pos_book, Book(b_name, b_author, b_stock, c));

                                ls.WriteWithColor("~ Data updated successfully ~", COLOR_SUCCESS_MESSAGE);
                                cout << endl;
                            } else {
                                ls.WriteWithColor("~ Book not found ~", COLOR_WARNING_MESSAGE);
                                cout << endl;
                            }
                        }
                            // delete book
                        else if (suboption_book == "3") {
                            cout << "-- Delete book --" << endl;
                            bool re = ls.searchBook();

                            if (re == false) {
                                cout << "There is no data found" << endl;
                                continue;
                            }

                            cout << "Please input book's Id >>";
                            int bookId;
                            cin >> bookId;

                            int pos = ls.searchBook(bookId);

                            if (pos != -1) {
                                ls.removeBook(pos);

                                ls.WriteWithColor("~ Data deleted successfully ~", COLOR_SUCCESS_MESSAGE);
                                cout << endl;
                            } else {
                                ls.WriteWithColor("~ Book not found ~", COLOR_WARNING_MESSAGE);
                                cout << endl;
                            }

                        }
                            // search book
                        else if (suboption_book == "4") {
                            cout << "-- Search books --" << endl;
                            bool re = ls.searchBook();
                            if (re == false) {
                                ls.WriteWithColor("There is no data found", COLOR_WARNING_MESSAGE);
                            }
                        }
                            // view all book
                        else if (suboption_book == "5") {
                            cout << "-- View all books --" << endl;
                            ls.displayBooks();
                        }
                            // back to menu
                        else if (suboption_book == "6") {
                            break;
                        } else {
                            ls.WriteWithColor("\nWrong Input\n", COLOR_WARNING_MESSAGE);
                        }
                    }
                }
                    // category
                else if (suboption_master_data == "2") {
                    while (true) {
                        string suboption_category;
                        ls.SetTextColor(COLOR_OPTIONS);
                        cout << "Category CRUD    " << endl
                             << "1. Insert        " << endl
                             << "2. Update        " << endl
                             << "3. Delete        " << endl
                             << "4. Search        " << endl
                             << "5. View all      " << endl
                             << "6. Back to menu  " << endl;
                        ls.ResetTextColor();

                        cin >> suboption_category;
                        // insert category
                        if (suboption_category == "1") {
                            addCategoryUI();
                        }
                            // update category
                        else if (suboption_category == "2") {
                            cout << "-- Update category --" << endl;
                            bool re = ls.searchCategory();

                            if (re == false) {
                                cout << "There is no data found" << endl;
                                continue;
                            }

                            cout << "Please input category's Id >>";
                            int categoryId;
                            cin >> categoryId;

                            int pos = ls.searchCategory(categoryId);
                            if (pos != -1) {
                                string c_name;

                                cout << "category's name >>";
                                cin >> c_name;

                                ls.updateCategory(pos, Category(c_name));

                                ls.WriteWithColor("~ Data updated successfully ~", COLOR_SUCCESS_MESSAGE);
                                cout << endl;
                            } else {
                                ls.WriteWithColor("~ Category not found ~", COLOR_WARNING_MESSAGE);
                                cout << endl;
                            }
                        }
                            // delete category
                        else if (suboption_category == "3") {
                            cout << "-- Delete category --" << endl;
                            bool re = ls.searchCategory();

                            if (re == false) {
                                cout << "There is no data found" << endl;
                                continue;
                            }

                            cout << "Please input category's Id >>";
                            int categoryId;
                            cin >> categoryId;

                            int pos = ls.searchCategory(categoryId);

                            if (pos != -1) {
                                ls.removeCategory(pos);

                                ls.WriteWithColor("~ Data deleted successfully ~", COLOR_SUCCESS_MESSAGE);
                                cout << endl;
                            } else {
                                ls.WriteWithColor("~ Category not found ~", COLOR_WARNING_MESSAGE);
                                cout << endl;
                            }

                        }
                            // search category
                        else if (suboption_category == "4") {
                            cout << "-- Search categories --" << endl;
                            bool re = ls.searchCategory();
                            if (re == false) {
                                cout << "There is no data found" << endl;
                            }
                        }
                            // view all categories
                        else if (suboption_category == "5") {
                            cout << "-- View all categories --" << endl;
                            ls.displayCategories();
                        }
                            // back to menu
                        else if (suboption_category == "6") {
                            break;
                        } else {
                            ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
                        }
                    }
                }
                    // user
                else if (suboption_master_data == "3") {
                    string suboption_user;
                    ls.SetTextColor(COLOR_OPTIONS);
                    cout << "User CRUD" << endl
                         << "1. Insert" << endl
                         << "2. Update" << endl
                         << "3. Delete" << endl
                         << "4. Search" << endl
                         << "5. View all" << endl;
                    ls.ResetTextColor();
                    cin >> option;
                    // insert user
                    if (suboption_user == "1") {
                        string name, username, password, confirm_password, role;

                        cout << "-- Add New User --" << endl;

                        cout << "name >>";
                        cin.ignore();
                        getline(cin, name);

                        cout << "username >>";
                        cin.ignore();
                        getline(cin, username);

                        cout << "password >>";
                        cin.ignore();
                        getline(cin, password);

                        cout << "confirm password >>";
                        cin.ignore();
                        getline(cin, confirm_password);
                        // check confirm password & password

                        cin.ignore();
                        cout << "Role [L = Library, A = Admin]>>";
                        getline(cin, role);

                        ls.addUser(User(name, username, password, role));
                    }
                        // update user
                    else if (suboption_user == "2") {

                    }
                        // delete user
                    else if (suboption_user == "3") {

                    }
                        // search user
                    else if (suboption_user == "4") {

                    }
                        // view all users
                    else if (suboption_user == "5") {

                    } else {
                        ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
                    }
                }

            }
                // view transaction
            else if (option == "2") {
                ls.viewAllTransactions();
            }
                // view borrowed books
            else if (option == "3") {
                ls.displayBorrowedBooks();
            }
                // view book's review
            else if (option == "4") {
                ls.viewBooksReview();
            } else if (option == "5") {
                ls.viewHighestRatedBooks();
            } else if (option == "6") {
                ls.viewHighestBorrowedBooks();
            }
                // logout
            else if (option == "7") {
                break;
            }
                // wrong input
            else {
                ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
            }
            cout << endl;
        }
    }
