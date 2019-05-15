cmake_minimum_required(VERSION 3.14)
project(Final_Project)

set(CMAKE_CXX_STANDARD 11)

add_executable(Final_Project main.cpp Model/book.h Model/book.cpp Model/category.h Model/category.cpp Model/transaction.cpp Model/transaction.h Model/user.cpp Model/user.h library_system.h library_system.cpp library_system_ui.h library_system_ui.cpp)