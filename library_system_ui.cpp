//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system_ui.h"

void LibrarySystemUI::run(){
    ls.addUser(User("test", "test", "test", "A"));

    int option;

    cout << "Welcome to Library System" << endl
         << "1. Login" << endl
         << "2. Register" << endl
         << "3. Exit" << endl;

    cin >> option;
    // login
    if(option == 1){
        string username, password;
        cout << "username >>";
        cin >> username;
        cout << "password >>";
        cin >> password;

        User u;
        bool login = ls.doLogin(username, password, u);
        if(login){
            if(u.getRole() == "A"){
                adminPage(u);
            }
            else if(u.getRole() == "L"){

            }
        }
        else{
            cout << "Username and password incorrect" << endl;
        }
    }
        // exit
    else if(option == 2){

    }
    else{
        cout << "Wrong Input" << endl;
    }
}
void LibrarySystemUI::adminPage(User currentUser){
    int option;
    while(true){
        cout << "Welcome " << currentUser.getName() <<" (admin)" << endl
             << "1. Master Data" << endl
             << "2. View Transaction" << endl
             << "3. View Borrowed Books" << endl
             << "4. Logout" << endl
             << ">>";

        cin >> option;
        // master data
        if(option == 1){
            int suboption_master_data;
            cout << "1. Book" << endl
                 << "2. Category" << endl
                 << "3. User" << endl
                 << ">>";
            cin >> suboption_master_data;

            // book
            if(suboption_master_data == 1){
                while(true){
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
                    if(suboption_book == 1){
                        cout << "-- Insert book --" << endl;
                        string b_name, b_author;
                        int b_stock;

                        cout << "book's name >>";
                        cin.ignore();
                        getline(cin, b_name);

                        cout << "book's author >>";
                        cin.ignore();
                        getline(cin, b_author);

                        cout << "book's stock >>";
                        cin >> b_stock;

                        ls.addBook(Book(b_name, b_author, b_stock));

                        cout << "~ Book added successfully ~" << endl;
                    }
                        // update book
                    else if(suboption_book == 2){
                        cout << "-- Update book --" << endl;
                        ls.searchBook();

                        cout << "Please input book's Id >>";
                        int bookId;
                        cin >> bookId;

                        int pos = ls.searchBook(bookId);
                        if(pos != -1){
//                            ls.updateBook()
                        }else{
                            cout << "Book not found";
                        }

                    }
                        // delete book
                    else if(suboption_book == 3){

                    }
                        // search book
                    else if(suboption_book == 4){
                        cout << "-- Search books --" << endl;
                        ls.searchBook();
                    }
                        // view all book
                    else if(suboption_book == 5){
                        cout << "-- View all books --" << endl;
                        ls.displayBooks();
                    }
                        // back to menu
                    else if(suboption_book == 6){
                        break;
                    }
                    else{
                        cout << "Wrong Input" << endl;
                    }
                }
            }
                // category
            else if(suboption_master_data == 2){

            }
                // user
            else if(suboption_master_data == 3){
                int suboption_user;
                cout << "User CRUD" << endl
                     << "1. Insert" << endl
                     << "2. Update" << endl
                     << "3. Delete" << endl
                     << "4. Search" << endl
                     << "5. View all" << endl;

                cin >> option;
                // insert user
                if(suboption_user == 1){
                    string name ,username, password, confirm_password, role;

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
                else if(suboption_user == 2){

                }
                    // delete user
                else if(suboption_user == 3){

                }
                    // search user
                else if(suboption_user == 4){

                }
                    // view all users
                else if(suboption_user == 5){

                }
            }
                // logout
            else if(suboption_master_data == 4){
                break;
            }
                // wrong input
            else{
                cout << "Wrong Input" << endl;
            }
            cout << endl;
        }
            // view transaction
        else if(option == 2){

        }
            // view borrowed books
        else if(option == 3){

        }
    }
}
