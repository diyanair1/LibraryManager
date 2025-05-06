// to store all the library functionalities
#ifndef LIBRARY_HPP
#define LIBRARY_HPP
#include <iostream>
#include <vector>
#include "book.hpp"
#include <fstream> // to read/write a file
#include <sstream> // to read line by line
using namespace std;


class Library{
    public:
        void load_from_txt(const string& filename, vector<Book>& library){
            ifstream in(filename);
            string line;

            while(getline(in, line)){
                stringstream ss(line);
                string bid, title, author, category, status;

                getline(ss, bid, ',');
                getline(ss, title, ',');
                getline(ss, author, ',');
                getline(ss, category, ',');
                getline(ss, status, ',');

                int bid_int = stoi(bid); // convert string to int
                Book newbook = Book(bid_int, title, author, category, status); // Create Book object
                library.push_back(newbook);
            }
        }
    
        void add_book(vector<Book>& library){
            int bid;
            string title, author, category, status;
            //bid,title,author,category,status
            cout << "Enter BID:";// ???
            cin >> bid;
            cin.ignore(); // Clear input buffer

            cout << "Enter Title: \n";
            getline(cin,title); // or cin >> title; which both takes input

            /*
            The getline() function extracts characters from the input stream
            and appends it to the string object until the delimiting character is encountered.
            */
            //first take every input, make book class object with those inputs and then push_back it into the library vector
            // push on github and update when changes are made
            cout << "Enter Author: \n";
            getline(cin, author);

            cout << "Enter category: \n";
            getline(cin, category);

            cout << "Enter status: ";
            getline(cin, status);

            Book newBook = Book(bid, title, author, category, status); // Create Book object
            library.push_back(newBook);
            
        }

        void list_library(vector<Book>& library){
            // displays all the books in the library line by line
            // library vector has to first be stored with data in books.txt 
            for (Book book : library){
                book.display();
            }
        }
        void remove_book(vector<Book>& library){
            //can we not use the find/search funtion here?


        }
};

#endif
