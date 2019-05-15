//
// Created by Hengky Sanjaya on 5/15/2019.
//

#include "library_system.h"

LibrarySystem::LibrarySystem(){
}
// -- User operations --
void LibrarySystem::addUser(User u){
    listUser.push_back(u);
}

void LibrarySystem::removeUser(int position){
    listUser.erase(listUser.begin() + position);
}

void LibrarySystem::updateUser(int position,User u){
    listUser[position].setName(u.getName());
    listUser[position].setUsername(u.getUsername());
    listUser[position].setPassword(u.getPassword());
    listUser[position].setRole(u.getRole());
    listUser[position].setLevel(u.getLevel());
    cout << "x";
}

vector<User> LibrarySystem::getListUser(){
    return listUser;
}

// -- Login --
bool LibrarySystem::doLogin(string username, string password, User& u){
    for(int i= 0 ; i < listUser.size();i++){
        User cur = listUser[i];
        if(cur.getUsername() == username && cur.getPassword() == password){
            u = cur;
            return true;
        }
    }
    return false;
}

// -- Book operations --

void LibrarySystem::addBook(Book b){
    listBook.push_back(b);
}

void LibrarySystem::removeBook(int position){
    listBook.erase(listBook.begin() + position);
}

void LibrarySystem::updateBook(int position,Book b){
    listBook[position].setName(b.getName());
    listBook[position].setAuthor(b.getAuthor());
    listBook[position].setStock(b.getStock());
    listBook[position].setRating(b.getRating());
}

int LibrarySystem::searchBook(int id) {
    for (int i = 0; i < listBook.size(); ++i) {
        if(listBook[i].getId() == id){
            return i;
        }
    }
    return -1;
}

void LibrarySystem::searchBook() {
    int suboption_book_search;
    string key;
    cout << "Search book by : "<< endl
         << "1. Name" << endl
         << "2. Author" << endl
         << ">>" ;
    cin >> suboption_book_search;

    if(suboption_book_search == 1){
        cout << "Input book name >>";
        cin >> key;
    }
    else if(suboption_book_search == 2){
        cout << "Input Author name >>";
        cin >> key;
    }

    printf("%-20s | %-20s | %-20s | %-20s | %-20s |\n", "ID","Name", "Author", "Stock", "Rating");

    for (int i = 0; i < listBook.size(); ++i) {
        if(suboption_book_search == 1){
            if(listBook[i].getName() == key){
                printf("%-20d | %-20s | %-20s | %-20d | %-20d |\n", listBook[i].getId() ,listBook[i].getName().c_str(),listBook[i].getAuthor().c_str() , listBook[i].getStock(), listBook[i].getRating());
            }
        }
        else if(suboption_book_search == 2){
            if(listBook[i].getAuthor() == key){
                printf("%-20d | %-20s | %-20s | %-20d | %-20d |\n", listBook[i].getId() ,listBook[i].getName().c_str(),listBook[i].getAuthor().c_str() , listBook[i].getStock(), listBook[i].getRating());
            }
        }
    }
    cout << endl;
}

void LibrarySystem::displayBooks(){
    printf("%-20s | %-20s | %-20s | %-20s | %-20s |\n", "ID","Name", "Author", "Stock", "Rating");
    for(int i = 0 ; i < listBook.size();i++){
        printf("%-20d | %-20s | %-20s | %-20d | %-20d |\n", listBook[i].getId() ,listBook[i].getName().c_str(),listBook[i].getAuthor().c_str() , listBook[i].getStock(), listBook[i].getRating());
    }
}

// -- Category operations --

void LibrarySystem::addCategory(Category c){
    listCategory.push_back(c);
}

void LibrarySystem::removeCategory(int position){
    listCategory.erase(listCategory.begin()+position);
}

void LibrarySystem::displayCategories(){

    cout << "Categories\n"
            "==========" << endl;
    for (int i = 0; i<listCategory.size(); i++){
        cout << listCategory[i].getName() << endl;
    }
}

// -- Transaction operations --
void LibrarySystem::addTransaction(Transaction t){
    listTransaction.push_back(t);
}


void LibrarySystem::testing(int a) {
    cout << "testing something" << endl;

}

void testfunc2(){
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



