//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system_ui.h"
#include "setup_variables.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

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

int LibrarySystemUI::addCategoryUI() {
    cout << "-- Insert category --" << endl;

    string c_name;
    cout << "category's name >>";
    cin >> c_name;

    int index = ls.addCategory(Category(c_name));

    cout << "~ Category added successfully ~" << endl;
    return index;
}

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

    string option;

    while (true) {
        string title = "=========================================\n"
                       "=         Welcome to HR Library         =\n"
                       "=========================================\n";
        ls.WriteWithColor(title, 9);

        ls.WriteWithColor("1. Login    \n"
                          "2. Register \n"
                          "3. Exit     \n"
                          ">>", COLOR_OPTIONS);

        cin >> option;
        // login
        if (option == "1") {
            string username, password;
            cout << "please enter your :" << endl;
            cout << "username >>";
            cin >> username;
            cout << "password >>";
            cin >> password;

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
                ls.WriteWithColor("Username and password incorrect", COLOR_WARNING_MESSAGE); // pink
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
                    ls.WriteWithColor("Username already exists", COLOR_WARNING_MESSAGE);
                } else {
                    break;
                }
            }

            cout << "password >>";
            cin >> password;

            while (true) {
                cout << "confirm password >>";
                cin >> confirm_password;

                if (confirm_password != password) {
                    ls.WriteWithColor("Confirm password and password must be the same", COLOR_WARNING_MESSAGE);
                } else {
                    break;
                }
            }

            ls.addUser(User(name, username, password, "L"));

            ls.WriteWithColor("Register success", COLOR_SUCCESS_MESSAGE);
        }
            // exit
        else if (option == "3") {
            break;
        } else {
            ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
        }
        cout << endl;
    }
}

void LibrarySystemUI::userPage(User currentUser) {

    int option, topBookoption, timeSpan;
    string year, month, day, date;
    while (true) {
        cout << endl;
        ls.WriteWithColor("Welcome " + currentUser.getName() + " (User)\n"
                                                               "1. Borrow book               \n"
                                                               "2. View Recommendation Books \n"
                                                               "3. View Top Books            \n"
                                                               "4. Return Book               \n"
                                                               "0. Logout                    \n"
                                                               ">>", COLOR_OPTIONS);

        cin >> option;

        if (option == 1) {
            int bookid;
            bool found = ls.searchBook();
            if (found == false) {
                ls.WriteWithColor("There is no data in the list", COLOR_WARNING_MESSAGE);
            } else {
                cout << "-- Borrow book --" << endl
                     << "Input book's id >>";
                cin >> bookid;

                int pos = ls.searchBook(bookid);
                if (pos == -1) {
                    ls.WriteWithColor("Sorry, book id not found", COLOR_WARNING_MESSAGE);
                } else {
                    ls.addTransaction(pos);

                    ls.WriteWithColor("~ Transaction success ~", COLOR_SUCCESS_MESSAGE);
                }
            }
        } else if (option == 2) {

        } else if (option == 3) {

            time_t theTime = time(NULL);
            struct tm *currTime = localtime(&theTime);

            day = to_string(currTime->tm_mday);
            month = to_string(currTime->tm_mon + 1);
            year = to_string(currTime->tm_year + 1900);

            date = year + "-" + month + "-" + day;

            ls.WriteWithColor("View By:\n"
                              "1. Rating         \n"
                              "2. Amount Borrowed\n"
                              ">>", COLOR_OPTIONS);

            cin >> topBookoption;

            ls.WriteWithColor("Time Span: \n"
                              "1. This Month \n"
                              "2. This Year  \n"
                              "3. All Time   \n"
                              ">>", COLOR_OPTIONS);

            cin >> timeSpan;

            if (topBookoption == 1) {
                ls.displayTopRatedBooks(date, timeSpan);
            } else if (topBookoption == 2) {
                ls.displayTopBorrowedBooks(date, timeSpan);
            }


        } else if (option == 4) {
            cout << "- Return Book -" << endl;

            int bookId;
            ls.displayBorrowedBooks(currentUser);
            cout << "Input Book Id you want to return >>";

            cin >> bookId;

            if (ls.returnBook(bookId)) {
                ls.WriteWithColor("Return book success", COLOR_SUCCESS_MESSAGE);
            } else {
                ls.WriteWithColor("Sorry, You dont borrow this book", COLOR_WARNING_MESSAGE);
            }
        } else if (option == 0) {
            break;
        } else {
            ls.WriteWithColor("Wrong Input", COLOR_WARNING_MESSAGE);
        }
    }
}

void LibrarySystemUI::adminPage(User currentUser) {
    int option;
    while (true) {
        cout << endl;
        ls.WriteWithColor("Welcome " + currentUser.getName() + " (admin)\n"
                                                               "1. Master Data         \n"
                                                               "2. View Transaction    \n"
                                                               "3. View Borrowed Books \n"
                                                               "4. Logout              \n"
                                                               ">>", COLOR_OPTIONS);

        cin >> option;
        // master data
        if (option == 1) {
            int suboption_master_data;
            cout << "1. Book" << endl
                 << "2. Category" << endl
                 << "3. User" << endl
                 << ">>";
            cin >> suboption_master_data;

            // book
            if (suboption_master_data == 1) {
                while (true) {
                    int suboption_book;
                    cout << "Book CRUD" << endl
                         << "1. Insert" << endl
                         << "2. Update" << endl
                         << "3. Delete" << endl
                         << "4. Search" << endl
                         << "5. View all" << endl
                         << "6. Back to menu" << endl;

                    cin >> suboption_book;
                    // insert book
                    if (suboption_book == 1) {
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

                        cout << "position" << pos << endl;
                        Category c = ls.getCategory(pos);
                        cout << "category name" << c.getName() << endl;

                        Book b = Book(b_name, b_author, b_stock, c);
                        cout << "category name2 " << b.getCategory().getName() << endl;
                        ls.addBook(b);

                        cout << "~ Book added successfully ~" << endl;
                    }
                        // update book
                    else if (suboption_book == 2) {
                        cout << "-- Update book --" << endl;
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
                            ls.updateBook(pos, Book(b_name, b_author, b_stock, c));

                            cout << "~ Data updated successfully ~" << endl;
                        } else {
                            cout << "~ Book not found ~";
                        }
                    }
                        // delete book
                    else if (suboption_book == 3) {
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

                            cout << "~ Data deleted successfully ~" << endl;
                        } else {
                            cout << "~ Book not found ~";
                        }

                    }
                        // search book
                    else if (suboption_book == 4) {
                        cout << "-- Search books --" << endl;
                        bool re = ls.searchBook();
                        if (re == false) {
                            cout << "There is no data found" << endl;
                        }
                    }
                        // view all book
                    else if (suboption_book == 5) {
                        cout << "-- View all books --" << endl;
                        ls.displayBooks();
                    }
                        // back to menu
                    else if (suboption_book == 6) {
                        break;
                    } else {
                        cout << "Wrong Input" << endl;
                    }
                }
            }
                // category
            else if (suboption_master_data == 2) {
                while (true) {
                    int suboption_category;
                    cout << "Category CRUD" << endl
                         << "1. Insert" << endl
                         << "2. Update" << endl
                         << "3. Delete" << endl
                         << "4. Search" << endl
                         << "5. View all" << endl
                         << "6. Back to menu" << endl;

                    cin >> suboption_category;
                    // insert category
                    if (suboption_category == 1) {
                        addCategoryUI();
                    }
                        // update category
                    else if (suboption_category == 2) {
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

                            cout << "~ Data updated successfully ~" << endl;
                        } else {
                            cout << "~ Category not found ~";
                        }
                    }
                        // delete category
                    else if (suboption_category == 3) {
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

                            cout << "~ Data deleted successfully ~" << endl;
                        } else {
                            cout << "~ Category not found ~";
                        }

                    }
                        // search category
                    else if (suboption_category == 4) {
                        cout << "-- Search categories --" << endl;
                        bool re = ls.searchCategory();
                        if (re == false) {
                            cout << "There is no data found" << endl;
                        }
                    }
                        // view all categories
                    else if (suboption_category == 5) {
                        cout << "-- View all categories --" << endl;
                        ls.displayCategories();
                    }
                        // back to menu
                    else if (suboption_category == 6) {
                        break;
                    } else {
                        cout << "Wrong Input" << endl;
                    }
                }
            }
                // user
            else if (suboption_master_data == 3) {
                int suboption_user;
                cout << "User CRUD" << endl
                     << "1. Insert" << endl
                     << "2. Update" << endl
                     << "3. Delete" << endl
                     << "4. Search" << endl
                     << "5. View all" << endl;

                cin >> option;
                // insert user
                if (suboption_user == 1) {
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
                else if (suboption_user == 2) {

                }
                    // delete user
                else if (suboption_user == 3) {

                }
                    // search user
                else if (suboption_user == 4) {

                }
                    // view all users
                else if (suboption_user == 5) {

                }
            }

        }
            // view transaction
        else if (option == 2) {
            ls.viewAllTransactions();
        }
            // view borrowed books
        else if (option == 3) {
            ls.displayBorrowedBooks();
        }
            // logout
        else if (option == 4) {
            break;
        }
            // wrong input
        else {
            cout << "Wrong Input" << endl;
        }
        cout << endl;
    }
}
