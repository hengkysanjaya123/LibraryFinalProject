//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system_ui.h"

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
    ls.addUser(User("test", "test", "test", "A"));
    ls.addUser(User("coba", "coba", "coba", "U"));

    int option;

    while (true) {
        cout << "Welcome to Library System" << endl
             << "1. Login" << endl
             << "2. Register" << endl
             << "3. Exit" << endl;

        cin >> option;
        // login
        if (option == 1) {
            string username, password;
            cout << "username >>";
            cin >> username;
            cout << "password >>";
            cin >> password;

            User u;
            bool login = ls.doLogin(username, password, u);
            if (login) {
                ls.setCurrentUser(u);

                if (u.getRole() == "A") {
                    adminPage(u);
                } else if (u.getRole() == "U") {
                    userPage(u);
                }
            } else {
                cout << "Username and password incorrect" << endl;
            }
        }
            // register
        else if (option == 2) {

        }
            // exit
        else if (option == 3) {
            break;
        } else {
            cout << "Wrong Input" << endl;
        }
        cout << endl;
    }
}

void LibrarySystemUI::userPage(User currentUser) {

    int option,topBookoption,timeSpan;
    string year,month,day,date;
    while (true) {
        cout << "Welcome " << currentUser.getName() << " (User)" << endl
             << "1. Borrow book" << endl
             <<  "2. "
             << "2. View Recommendation Books" << endl
             << "3. View Top Books" << endl
             << "4. Return Book"
             << "0. Logout" << endl
             << ">>";

        cin >> option;

        if (option == 1) {
            int bookid;
            bool found = ls.searchBook();
            if (found == false) {
                cout << "There is no data in the list" << endl;
            } else {
                cout << "-- Borrow book --" << endl
                     << "Input book's id >>";
                cin >> bookid;

                int pos = ls.searchBook(bookid);
                if (pos == -1) {
                    cout << "Sorry, book id not found" << endl;
                } else {
                    ls.addTransaction(pos);

                    cout << "~ Transaction success ~" << endl;
                }
            }
        } else if (option == 3){

            time_t theTime = time(NULL);
            struct tm *currTime = localtime(&theTime);

            day = to_string(currTime->tm_mday);
            month = to_string(currTime->tm_mon + 1);
            year = to_string(currTime->tm_year + 1900);

            date = year + "-" + month + "-" + day;

            cout << "View By: " << endl
                 << "1. Rating" << endl
                 << "2. Amount Borrowed" << endl
                 << ">>";

            cin >> topBookoption;

            cout << "Time Span: " << endl
                 << "1. This Month" << endl
                 << "2. This Year" << endl
                 << "3. All Time" << endl
                 << ">>";

            cin >> timeSpan;

            if (topBookoption == 1){
                ls.displayTopRatedBooks(date, timeSpan);
            }

            else if (topBookoption == 2){
                ls.displayTopBorrowedBooks(date, timeSpan);
            }


        } else if (option == 0) {
            break;
        } else {
            cout << "Wrong Input" << endl;
        }
    }
}

void LibrarySystemUI::adminPage(User currentUser) {
    int option;
    while (true) {
        cout << "Welcome " << currentUser.getName() << " (admin)" << endl
             << "1. Master Data" << endl
             << "2. View Transaction" << endl
             << "3. View Borrowed Books" << endl
             << "4. Logout" << endl
             << ">>";

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

        }
            // view borrowed books
        else if (option == 3) {

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
